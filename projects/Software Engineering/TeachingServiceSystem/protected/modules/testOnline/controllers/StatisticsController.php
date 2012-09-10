<?php

class StatisticsController extends Controller
{
	/**
	 * @var string the default layout for the views. Defaults to '//layouts/column2', meaning
	 * using two-column layout. See 'protected/views/layouts/column2.php'.
	 */
	public $layout='//layouts/column2';

	/**
	 * @return array action filters
	 */
	public function filters()
	{
		return array(
			'rights', // perform access control for CRUD operations
		);
	}

	/**
	 * Specifies the access control rules.
	 * This method is used by the 'accessControl' filter.
	 * @return array access control rules
	 */
	public function accessRules()
	{
		return array(
			array('allow',  // allow all users to perform 'index' and 'view' actions
				'actions'=>array('index','view'),
				'users'=>array('*'),
			),
			array('allow', // allow authenticated user to perform 'create' and 'update' actions
				'actions'=>array('create','update'),
				'users'=>array('@'),
			),
			array('allow', // allow admin user to perform 'admin' and 'delete' actions
				'actions'=>array('admin','delete'),
				'users'=>array('admin'),
			),
			//array('deny',  // deny all users
			//	'users'=>array('*'),
			//),
			array('allow',
			    'actions'=>array('showprob', 'showpaper', 'showstu'),
			    'users'=>array('admin'),
			),
			
		);
	}

	/**
	 * Displays a particular model.
	 * @param integer $id the ID of the model to be displayed
	 */

	public function actionView($id)
	{
		$tmp = $_GET['id'];
		if ($tmp != "") {
		    $this->render('view',array(
			    'model'=>$this->loadModel($tmp),
		    ));
		} else {
		    $this->render('view',array(
			    'model'=>$this->loadModel($tmp),
		    ));
		}
	}

	/**
	 * Creates a new model.
	 * If creation is successful, the browser will be redirected to the 'view' page.
	 */
	public function actionCreate()
	{
		$model=new statistics;

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);

		if(isset($_POST['statistics']))
		{
			$model->attributes=$_POST['statistics'];
			if($model->save())
				$this->redirect(array('view','id'=>$model->id));
		}

		$this->render('create',array(
			'model'=>$model,
		));
	}
	
	public function actionView1() {
		//进入题目未做过时候显示的结果
		$model=new statistics;
		$model->unsetAttributes();  // clear any default values
		
		$this->render('view1',array(
			'model'=>$model,
		));
	}	
	public function actionShowstu()
	{
		// 进入显示学生成绩分析的action
		$model=new statistics;
		$model->unsetAttributes();  // clear any default values
		if(isset($_GET['statistics']))
			$model->attributes=$_GET['statistics'];

		$this->render('showstu',array(
			'model'=>$model,
		));
	}	

	public static function getRatio($num, $answer) {
		//计算答题正确率，暂时不用
		return '0.00';
	}
	public static function  getAllGrades($paperID) {
		//根据试卷id获取参加该试卷的学生的成绩
		$condi = new CDbCriteria ();
		$condi->compare ( 'paper_id', $paperID );
		$paperProbPairs = StuTestStatus::model ()->findAll ( $condi );
		$data = array();
		$data1 = array();
		foreach($paperProbPairs as $i => $paperProbPair)
		{
			$data[$i] = $paperProbPair->stu_id;
			$dt1 = TestInfoComponent::getStudentScore($paperProbPair->stu_id);
		    foreach ($dt1 as $key => $value) {
    			if ($key == $paperID) $data1[$i] = $value;
			}			
			$i++;
		}
		return $data1;
	}
	//FIXME: 给蛋蛋的接口，addProb(1234, 'A');
	public static function addProb($id, $answer) {
		//用于记录试题答题情况
		//添加题目回答结果情况，若第一次回答题目，则创建新的列表，否则更新原有列表信息
		$model = statistics::model()->findByAttributes($attributes = array('pro_id' => $id));
		if ($model == NULL) 
		{//不存在信息，创建信息
			$model = new statistics;
			$model->pro_id = $id;
			$model->a = 0;
	    	$model->b = 0;
			$model->c = 0;
			$model->d = 0;
			if ($answer == 'A' || $answer == 'T') $model->a = $model->a + 1;
			if ($answer == 'B' || $answer == 'F') $model->b = $model->b + 1;
			if ($answer == 'C') $model->c = $model->c + 1;
			if ($answer == 'D') $model->d = $model->d + 1;
			if ($answer == ' ') $model->done = 1;
			$model->save();
		} 
		else 
		{//存在信息，更新信息		    
			if ($answer == 'A' || $answer == 'T') $model->a = $model->a + 1;
			if ($answer == 'B' || $answer == 'F') $model->b = $model->b + 1;
			if ($answer == 'C') $model->c = $model->c + 1;
			if ($answer == 'D') $model->d = $model->d + 1;
			if ($answer == ' ') $model->done = $model->done + 1;
			$model->save();
		}
	
	}
	public function actionShowprob()
	{
		//进入题目显示列表的action
		$model=new statistics;
		$model->unsetAttributes();  // clear any default values
		if(isset($_GET['statistics']))
			$model->attributes=$_GET['statistics'];

		$this->render('showprob',array(
			'model'=>$model,
		));
	}

	public function actionShowpaper()
	{
	    //进入试卷显示列表的action
		$model=new statistics;
		$model->unsetAttributes();  // clear any default values
		if(isset($_GET['statistics']))
			$model->attributes=$_GET['statistics'];
		$this->render('showpaper',array(
			'model'=>$model,
		));
	}	
	/**
	 * Updates a particular model.
	 * If update is successful, the browser will be redirected to the 'view' page.
	 * @param integer $id the ID of the model to be updated
	 */
	public function actionUpdate($id)
	{
		$model=$this->loadModel($id);

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);

		if(isset($_POST['statistics']))
		{
			$model->attributes=$_POST['statistics'];
			if($model->save())
				$this->redirect(array('view','id'=>$model->id));
		}

		$this->render('update',array(
			'model'=>$model,
		));
	}

	/**
	 * Deletes a particular model.
	 * If deletion is successful, the browser will be redirected to the 'admin' page.
	 * @param integer $id the ID of the model to be deleted
	 */
	public function actionDelete($id)
	{
		if(Yii::app()->request->isPostRequest)
		{
			// we only allow deletion via POST request
			$this->loadModel($id)->delete();

			// if AJAX request (triggered by deletion via admin grid view), we should not redirect the browser
			if(!isset($_GET['ajax']))
				$this->redirect(isset($_POST['returnUrl']) ? $_POST['returnUrl'] : array('admin'));
		}
		else
			throw new CHttpException(400,'Invalid request. Please do not repeat this request again.');
	}

	/**
	 * Lists all models.
	 */
	public function actionIndex()
	{
		$dataProvider=new CActiveDataProvider('statistics');
		$this->render('index',array(
			'dataProvider'=>$dataProvider,
		));
	}

	/**
	 * Manages all models.
	 */
	public function actionAdmin()
	{
		$model=new statistics('search');
		$model->unsetAttributes();  // clear any default values
		if(isset($_GET['statistics']))
			$model->attributes=$_GET['statistics'];

		$this->render('admin',array(
			'model'=>$model,
		));
	}

	/**
	 * Returns the data model based on the primary key given in the GET variable.
	 * If the data model is not found, an HTTP exception will be raised.
	 * @param integer the ID of the model to be loaded
	 */
	public function loadModel($id)
	{
		$model=statistics::model()->findByPk($id);
		if($model===null) {
			$this->redirect(array("statistics/view1"));
			//throw new CHttpException(404,'The requested page does not exist.');
		}
		return $model;
	}

	/**
	 * Performs the AJAX validation.
	 * @param CModel the model to be validated
	 */
	protected function performAjaxValidation($model)
	{
		if(isset($_POST['ajax']) && $_POST['ajax']==='statistics-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
	}
}
