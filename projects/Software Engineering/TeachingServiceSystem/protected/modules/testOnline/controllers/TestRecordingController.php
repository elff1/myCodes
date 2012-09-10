<?php

class TestRecordingController extends Controller {
	/**
	 *
	 * @var string the default layout for the views. Defaults to
	 *      '//layouts/column2', meaning
	 *      using two-column layout. See 'protected/views/layouts/column2.php'.
	 */
	public $layout = '//layouts/column2';
	
	/**
	 *
	 * @return array action filters
	 */
	public function filters() {
		return array (
				'rights'  // perform access control for CRUD operations using RIGHTS module
				)
		;
	}
	
	private static $TIME_NAME = "start_time";
	private static $SUSPEND_NAME = "suspend_flag";
	/* 
	 * init @param paperId and @param stuId from accountComponents
	 * @see RController::init()
	 */
	public function init() {
		parent::init ();
		
		$this->paperId = AccountComponent::getSelected_paper_id ();
		$this->stuId = AccountComponent::getSelected_Student_id ();
		$this->suspendFlag = Yii::app()->user->getState(self::$SUSPEND_NAME,false);
	}
	/**
	 * Specifies the access control rules.
	 * This method is used by the 'accessControl' filter.
	 * @obsolete, not used
	 * @return array access control rules
	 */
// 	public function accessRules() {
// 		return array (
// 				array (
// 						'allow', // allow all users to perform 'index' and
// 						         // 'view' actions
// 						'actions' => array (
// 								'index',
// 								'view' 
// 						),
// 						'users' => array (
// 								'*' 
// 						) 
// 				),
// 				array (
// 						'allow', // allow authenticated user to perform 'create'
// 						         // and 'update' actions
// 						'actions' => array (
// 								'create',
// 								'update' 
// 						),
// 						'users' => array (
// 								'@' 
// 						) 
// 				),
// 				array (
// 						'allow', // allow admin user to perform 'admin' and
// 						         // 'delete' actions
// 						'actions' => array (
// 								'admin',
// 								'delete' 
// 						),
// 						'users' => array (
// 								'admin' 
// 						) 
// 				),
// 				array (
// 						'deny', // deny all users
// 						'users' => array (
// 								'*' 
// 						) 
// 				) 
// 		);
// 	}
	
	/**
	 * @var finish_reasons: list reasons for why the test finishes
	 */
	private static $FINISH_REASON = array (
			"Nothing happens.",
			"Due date passed.",
			"You have already submit this test.",
			"You have problems not done" 
	);
	private $paperId;
	private $stuId;
	public $suspendFlag;
	/**
	 *
	 * @return integer time left for paper @param paperId
	 * @return -1 for non time limit;
	 * @return -2 for test not started
	 * @return -3 for test already ended
	 * @return -4 for test not exist
	 */
	public function actionGetTimeLeft() {
		$paperId = $this->paperId;
		$paper = PaperBank::model ()->findByPk ( $paperId );
		if($paper === null)
		{
			return array(-4,0);
		}
		$timelimit = $paper->timelimit;
		$tarr = explode ( ":", $timelimit );
		$ava_second = $tarr [0] * 3600 + $tarr [1] * 60 + $tarr [2];
		if($ava_second === 0)
		{
			return array(-1,0);
			Yii::app()->end();
		}
		$status = StuTestStatus::model ()->findByAttributes ( array (
				'stu_id' => $this->stuId,
				'paper_id' => $this->paperId 
		) );
		$retvar = -4;
		if ($status === null)
			return array(-2,0);
		else{
			$elapsed_second =  $status->elapse_sec;
			if ($elapsed_second > $ava_second) {
				return array(-3,0);
			} else
				return array($status->isactive?1:-5,$ava_second-$elapsed_second);
		}
		return $retvar;
	}
	/**
	 * check if the current test has end
	 * @return 0 for not done, 1 for all ok
	 */
	public function actionEndTestCheck() {
		$condi = new CDbCriteria ();
		$condi->compare ( 'paper_id', $this->paperId );
		$totCnt = Paper::model ()->count ( $condi );
		
		$condi = new CDbCriteria ();
		$condi->compare ( 'testRecording.student_id', $this->stuId );
		$condi->compare ( 'paper_id', $this->paperId );
		$doCnt = Paper::model ()->with ( "testRecording" )->count ( $condi );
		// TODO: we assume that for each student, a paper-pro-id will only
		// shadow a row in test_student, so we use the count of paper row
		// directly as recording count
		echo ($doCnt < $totCnt);
		Yii::app ()->end ();
	}
	/**
	 * commit all problems of current test and notify statistic module
	 */
	private function dealAllProInTest() {
		$condi = new CDbCriteria ();
		$condi->compare ( 'paper_id', $this->paperId );
		$paperProbPairs = Paper::model ()->findAll ( $condi );
		foreach ( $paperProbPairs as $paperProbPair ) {
			StatisticsController::addProb ( $paperProbPair->pro_id, ' ' );
		
		}
		$condi = new CDbCriteria ();
		$condi->compare ( 'testRecording.student_id', $this->stuId );
		$condi->compare ( 'paper_id', $this->paperId );
		$stuPaperPairs = Paper::model ()->with ( "testRecording" )->findAll ( $condi );
		foreach ( $stuPaperPairs as $stuPaperPair ) {
			$recordings = $stuPaperPair->testRecording;
			foreach ( $recordings as $recording ) {
				StatisticsController::addProb ( $stuPaperPair->pro_id, $recording->choose );
			}
		}
	}
	
	private function fetchElapseSec($status)
	{
		if($status->isactive == 1){
			$ret =  (time() - strtotime($status->last_active_time));
		}
		else
			$ret = 0;
		return $ret>0?$ret:0;
	}
	/**
	 *
	 * @param boolean $manualStop        	
	 * @return if manualStop is true, then the user want to submit the test,
	 *         else it's a TLE-submit or try to submit again
	 */
	private function validateTestTime($manualStop) {
		// $this->paperId = 2;
		$timelimit = PaperBank::model ()->findByPk ( $this->paperId )->timelimit;
		
		if ($timelimit == "00:00:00") {
			return 0;
		}
		$status = StuTestStatus::model ()->findByAttributes ( array (
				'stu_id' => $this->stuId,
				'paper_id' => $this->paperId 
		) );
		if ($status === null) {
			// this means this user has never attended this test, then we create
			// it
			$status = new StuTestStatus ();
			$status->last_active_time = date ( 'Y-m-d H:i:s' );
			$status->elapse_sec = $this->fetchElapseSec($status);
			$status->stu_id = $this->stuId;
			$status->paper_id = $this->paperId;
			
			$status->save ();
			$this->suspendFlag = false;
			return 0;
		} else {
		
			if (/*$status->end_time != null || */$status->is_submit == 1) {
				//TODO: if end_time isn't null, this already means user has submit, so is_submit must be 1
				$this->canSubmit = false;
				return 2;
			}
			//TODO : handle leave
			//$status->isactive = $status->user_out_state;
			//TODO : handle leave
			$elapsed_second = $status->elapse_sec + $this->fetchElapseSec($status);
			$tarr = explode ( ":", $timelimit );
			$ava_second = $tarr [0] * 3600 + $tarr [1] * 60 + $tarr [2];
			$ava_second = ( int ) $ava_second;
			
			if ($manualStop === false) {
				if ($elapsed_second > $ava_second) {
					$status->elapse_sec = $elapsed_second;
					$status->last_active_time = date ( 'Y-m-d H:i:s' );
					$status->is_submit = 1;
					
					$status->save ();
					$this->dealAllProInTest ();
					$this->canSubmit = false;
					$this->suspendFlag = !$status->isactive;
					return 1;
				} 
				else
				{
					$status->elapse_sec = $elapsed_second;
					$status->last_active_time = date ( 'Y-m-d H:i:s' );
					
					$status->save ();
					$this->suspendFlag = !$status->isactive;
					return 0;
				}
			} else {
				$status->elapse_sec = $elapsed_second;
				$status->is_submit = 1;
				//$status->last_active_time = date ( 'Y-m-d H:i:s' );
				$status->save ();
				$this->dealAllProInTest ();
				$this->canSubmit = false;
				$this->suspendFlag = !$status->isactive;
				Yii::app ()->user->setFlash ( 'finish_reason', self::$FINISH_REASON [2] );
				return 2;
			}
		}
	}
	
	public function actionResume()
	{
		$status = StuTestStatus::model ()->findByAttributes ( array (
				'stu_id' => $this->stuId,
				'paper_id' => $this->paperId
		) );
		$status->isactive = 1;
		//TODO : handle leave
		//
		//$status->user_out_state = 1;
		//TODO : handle leave
		$status->last_active_time = date ( 'Y-m-d H:i:s' );
		
		$status->save();
		$this->suspendFlag = false;
		$this->redirect($_SERVER['HTTP_REFERER'] );
	}
	
	public function actionSuspend()
	{
		$status = StuTestStatus::model ()->findByAttributes ( array (
				'stu_id' => $this->stuId,
				'paper_id' => $this->paperId
		) );
		$elapsed_second = $status->elapse_sec + $this->fetchElapseSec($status);
		$status->isactive = 0;
		//TODO : handle leave
		//
		//$status->user_out_state = 0;
		//TODO : handle leave
		$status->elapse_sec = $elapsed_second;
		$status->save();
		$this->suspendFlag = true;
		$this->redirect($_SERVER['HTTP_REFERER'] );
	}
	/**
	 *
	 * @var boolean seems no use
	 */
	public $canSubmit = true;
	/**
	 * perform TLE check or resubmit test for this module and control redirect
	 */
	private function checkDateLimit() {
// 		//if($this->suspendFlag)
// 		//	return;
// 		if(!isset(Yii::app()->session["Paper ".$this->paperId])){
// 			Yii::app()->session["Paper ".$this->paperId] = date ( 'Y-m-d H:i:s' );
// 		}
		$ret = $this->validateTestTime ( false );
		if ($ret != 0) {
			Yii::app ()->user->setFlash ( 'finish_reason', self::$FINISH_REASON [$ret] );
			$this->redirect ( array (
					'finishTest' 
			) );
		}
		;
	}
	/**
	 * corresponding page for finishTest 
	 */
	public function actionFinishTest() {
		$this->validateTestTime ( true );
		$this->render ( "testFinished" );
	}
	
	/**
	 * Displays a particular model.
	 *
	 * @param integer $id
	 *        	the ID of the model to be displayed
	 */
	public function actionView($id) {
		$this->render ( 'view', array (
				'model' => $this->loadModel ( $id ) 
		) );
	}

	public function actionUserExit()
	{
		$status = StuTestStatus::model ()->findByAttributes ( array (
				'stu_id' => $this->stuId,
				'paper_id' => $this->paperId
		) );
		$status->user_out_state = $status->isactive;
		$status->isactive = 0;
		$status->save();
	}
	public function actionBeginTest()
	{
		$status = StuTestStatus::model ()->findByAttributes ( array (
				'stu_id' => $this->stuId,
				'paper_id' => $this->paperId
		) );
		if ($status === null) {
			
		} else {	
		$status->isactive = $status->user_out_state;
		}
		$this->redirect(array("goTest"));
	}
	/**
	 * main function for a test
	 * first perform date check, then separate the pages
	 * also deal with save case
	 */
	public function actionGoTest() {
		$this->checkDateLimit ();
		$models = array ();
		$this->stuId = AccountComponent::getSelected_Student_id();
		$condi = new CDbCriteria ();
		$condi->compare ( 'paper_id', $this->paperId );
		
		$count = Paper::model ()->count ( $condi );
		$pages = new CPagination ( $count );
		
		$pages->pageSize = 1;
		$pages->applyLimit ( $condi );
		
		$i = 0;
		if (isset ( $_POST ['TestRecording'] )) {
			
			$allok = true;
			$props = $_POST ['TestRecording'];
			// $pageNum = $_POST ['pageNum'];
			foreach ( $props as $i => $prop ) {
				$model = TestRecording::model ()->findByAttributes ( array (
						'student_id' => $this->stuId,
						'paper_pro_id' => $prop ['paper_pro_id'] 
				) );
				if ($model === null)
					$model = new TestRecording ();
				$model->attributes = $prop;
				$model->student_id = $this->stuId;
				$model->score = 0;
				
				$allok = $allok && $model->save ();
				$models [$i ++] = $model;
			}
			if ($allok === true) {
				$curPagePos = $pages->currentPage;
				if ($curPagePos === $pages->getPageCount () - 1) {
				
				} else
					$this->redirect ( array (
							'goTest',
							$pages->pageVar => $pages->currentPage + 2 
					) );
			}
		} else {
			$paperProbPairs = Paper::model ()->findAll ( $condi );
			foreach ( $paperProbPairs as $paperProbPair ) {
				$model = TestRecording::model ()->findByAttributes ( array (
						'student_id' => $this->stuId,
						'paper_pro_id' => $paperProbPair->id 
				) );
				if ($model === null) {
					$model = new TestRecording ();
					$model->paper_pro_id = $paperProbPair->id;
				}
				$models [$i ++] = $model;
			}
		}
		$this->render ( 'goTest', array (
				'models' => $models,
				'pages' => $pages 
		) );
	}
// 	/**
// 	 * Creates a new model.
// 	 * If creation is successful, the browser will be redirected to the 'view'
// 	 * page.
// 	 */
// 	public function actionCreate() {
		
// 		$model = new TestRecording ();
// 		// Uncomment the following line if AJAX validation is needed
// 		// $this->performAjaxValidation($model);
		
// 		if (isset ( $_POST ['TestRecording'] )) {
// 			$model->attributes = $_POST ['TestRecording'];
// 			$model->student_id = 45; // for test
// 			$model->score = 0;
// 			$model->is_commit = 0;
// 			if ($model->save ())
// 				$this->redirect ( array (
// 						'view',
// 						'id' => $model->id 
// 				) );
// 		}
		
// 		// $this->render ( 'create', array (
// 		// 'model' => $model
// 		// r) );
// 	}
	
// 	/**
// 	 * Updates a particular model.
// 	 * If update is successful, the browser will be redirected to the 'view'
// 	 * page.
// 	 *
// 	 * @param integer $id
// 	 *        	the ID of the model to be updated
// 	 */
// 	public function actionUpdate($id) {
// 		$model = $this->loadModel ( $id );
		
// 		// Uncomment the following line if AJAX validation is needed
// 		// $this->performAjaxValidation($model);
		
// 		if (isset ( $_POST ['TestRecording'] )) {
// 			$model->attributes = $_POST ['TestRecording'];
// 			if ($model->save ())
// 				$this->redirect ( array (
// 						'view',
// 						'id' => $model->id 
// 				) );
// 		}
		
// 		$this->render ( 'update', array (
// 				'model' => $model 
// 		) );
// 	}
	
// 	/**
// 	 * Deletes a particular model.
// 	 * If deletion is successful, the browser will be redirected to the 'admin'
// 	 * page.
// 	 *
// 	 * @param integer $id
// 	 *        	the ID of the model to be deleted
// 	 */
// 	public function actionDelete($id) {
// 		if (Yii::app ()->request->isPostRequest) {
// 			// we only allow deletion via POST request
// 			$this->loadModel ( $id )->delete ();
			
// 			// if AJAX request (triggered by deletion via admin grid view), we
// 			// should not redirect the browser
// 			if (! isset ( $_GET ['ajax'] ))
// 				$this->redirect ( isset ( $_POST ['returnUrl'] ) ? $_POST ['returnUrl'] : array (
// 						'admin' 
// 				) );
// 		} else
// 			throw new CHttpException ( 400, 'Invalid request. Please do not repeat this request again.' );
// 	}
	
	/**
	 * redirect to goTest
	 */
	public function actionIndex() {
		$this->redirect ( array (
				'goTest' 
		) );
	}
	
// 	/**
// 	 * Manages all models.
// 	 */
// 	public function actionAdmin() {
// 		$model = new TestRecording ( 'search' );
// 		$model->unsetAttributes (); // clear any default values
// 		if (isset ( $_GET ['TestRecording'] ))
// 			$model->attributes = $_GET ['TestRecording'];
		
// 		$this->render ( 'admin', array (
// 				'model' => $model 
// 		) );
// 	}
	
// 	/**
// 	 * Returns the data model based on the primary key given in the GET
// 	 * variable.
// 	 * If the data model is not found, an HTTP exception will be raised.
// 	 *
// 	 * @param
// 	 *        	integer the ID of the model to be loaded
// 	 */
// 	public function loadModel($id) {
// 		$model = TestRecording::model ()->findByPk ( $id );
// 		if ($model === null)
// 			throw new CHttpException ( 404, 'The requested page does not exist.' );
// 		return $model;
// 	}
	
// 	/**
// 	 * Performs the AJAX validation.
// 	 *
// 	 * @param
// 	 *        	CModel the model to be validated
// 	 */
// 	protected function performAjaxValidation($model) {
// 		if (isset ( $_POST ['ajax'] ) && $_POST ['ajax'] === 'test-recording-form') {
// 			echo CActiveForm::validate ( $model );
// 			Yii::app ()->end ();
// 		}
// 	}
}
