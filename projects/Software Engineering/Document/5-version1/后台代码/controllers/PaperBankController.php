<?php

class PaperBankController extends Controller
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
				'users'=>array('@'),
			),
			array('allow', // allow authenticated user to perform 'create' and 'update' actions
				'actions'=>array('create','update'),
				'users'=>array('@'),
			),
			array('allow', // allow admin user to perform 'admin' and 'delete' actions
				'actions'=>array('admin','delete'),
				'users'=>array('admin'),
			),
			array('deny',  // deny all users
				'users'=>array('*'),
			),
		);
	}

	/**
	 * Displays a particular model.
	 * @param integer $id the ID of the model to be displayed
	 */
	public function actionView($id)
	{
		$this->render('view',array(
			'model'=>$this->loadModel($id),
		));
	}

	/**
	 * Creates a new model.
	 * If creation is successful, the browser will be redirected to the 'view' page.
	 */
	public function actionCreate()
	{
		$model=new PaperBank;

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);

		if(isset($_POST['PaperBank']))
		{
			$model->attributes=$_POST['PaperBank'];
			$model->teacher_id=AccountComponent::getSelected_Teacher_id();
			$model->course_id=AccountComponent::getSelected_course_id();
			$model->is_publish=0;
			if($model->save()){
				Yii::app()->session->add('selected_paper_id',$model->id);
				$this->redirect(array('view','id'=>$model->id));
			}
		}

		$this->render('create',array(
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

		if(isset($_POST['PaperBank']))
		{
			$model->attributes=$_POST['PaperBank'];
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
		$this->render('index',array(
			'dataProvider'=>PaperBankController::getPapers(),
		));
	}

	/**
	 * Manages all models.
	 */
	public function actionAdmin()
	{
		$model=new PaperBank('search');
		$model->unsetAttributes();  // clear any default values
		if(isset($_GET['PaperBank']))
			$model->attributes=$_GET['PaperBank'];

		$this->render('admin',array(
			'model'=>$model,
		));
	}

	
	public function actionGoAutoAdd($id){
		$model=new AutoAdd;
		$this->render('autoView',array(
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
		$model=PaperBank::model()->findByPk($id);
		if($model===null)
			throw new CHttpException(404,'The requested page does not exist.');
		return $model;
	}

	/**
	 * Performs the AJAX validation.
	 * @param CModel the model to be validated
	 */
	protected function performAjaxValidation($model)
	{
		if(isset($_POST['ajax']) && $_POST['ajax']==='paper-bank-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
	}

	/**
	 * Get the the paper list of a course.
	 * @return DataProvider of the PaperBank list
	 */
	public static function getPapers() {
		$criteria = new CDbCriteria;
		if(AccountComponent::getUserType()===UserAuthentication::TYPE_TEACHER)//teacher
			$criteria->compare('teacher_id',AccountComponent::getUserID());
		//administor choose as a teacher
		else if((AccountComponent::getUserType()===UserAuthentication::TYPE_ADMIN|AccountComponent::getUserType()===UserAuthentication::TYPE_SYSTEM_ADMIN)&&AccountComponent::getUserSelectedType()===UserAuthentication::TYPE_TEACHER)
			$criteria->compare('teacher_id',AccountComponent::getSelected_Teacher_id());
 		else{//a student or an administor choosing as a student
 			$criteria->compare('teacher_id',AccountComponent::getStudentTeacherID());
 			$criteria->compare('is_publish',1);
 		}
		$criteria->compare('course_id',AccountComponent::getSelected_course_id());
		return new CActiveDataProvider(PaperBank::model(),array('criteria'=>$criteria));
	}
	
	/**
	 * Get the the unused paper list of a course.
	 * @return DataProvider of the unused PaperBank list
	 */
	public static function getUnusedQuestions($paper_id)
	{
		$course_id = AccountComponent::getSelected_course_id();
		
		$models = Paper::model()->findAllByAttributes(array('paper_id'=>$paper_id));
		$used_problems = CHtml::listData($models,'id','pro_id');
		
		$cond = new CDbCriteria ();
		$cond->addNotInCondition('id', $used_problems);
		$cond->compare('course_id', $course_id);
		$cond->compare('teacher_id',AccountComponent::getSelected_Teacher_id());
		
		//$condi->addNotInCondition( 'id', $used_questions);
		return new CActiveDataProvider(QuestionBank::model(),array('criteria'=>$cond));
	}

	/**
	 * Get the the unused paper ID list of a course.
	 * @return Array of the unused PaperBank ID list
	 */
	public static function getUnusedQuestionsID()
	{
		$course_id = AccountComponent::getSelected_course_id();
		$paper_id = AccountComponent::getSelected_paper_id();
		
		$models = Paper::model()->findAllByAttributes(array('paper_id'=>$paper_id));
		$used_problems = CHtml::listData($models,'id','pro_id');
		
		$cond = new CDbCriteria ();
		$cond->addNotInCondition('id', $used_problems);
		$cond->compare('course_id', $course_id);
		$cond->compare('teacher_id',AccountComponent::getSelected_Teacher_id());
		
		return CHtml::listData(QuestionBank::model()->findAll($cond),'id','id');
		//return new CActiveDataProvider(QuestionBank::model(),array('criteria'=>$cond));
	}
}
