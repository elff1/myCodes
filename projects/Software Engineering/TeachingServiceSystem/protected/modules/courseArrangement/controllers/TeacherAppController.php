<?php

class TeacherAppController extends Controller
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
				'users'=>array('admin'),
			),
			/*
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
			*/
			array('deny',  // deny all users
				'users'=>array('?'),
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
		$model=new TeacherApp;

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);

		if(isset($_POST['TeacherApp']))
		{
			$model->attributes=$_POST['TeacherApp'];
			$model->setTeacherId();
			$model->setAppTime();
			//$modle->setCourseID();
			
			if($model->save())
				$this->redirect(array('view','id'=>$model->id));
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

		if(isset($_POST['TeacherApp']))
		{
			$model->attributes=$_POST['TeacherApp'];
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
		$dataProvider=new CActiveDataProvider('TeacherApp',array(   
		'criteria' => array(   
        'condition'=>'teacherID = '.Yii::app()->user->id,   

		),   
		'pagination'=>array(   
        'pageSize'=>10,   
        'currentPage'=>0,   
		),   
		)); 
		
		$this->render('index',array(
			'dataProvider'=>$dataProvider,
		));
	}

	
	/**
	 * for admin to confirm.
	 */
	public function actionConfirm()
	{
		//$dataProvider=new CActiveDataProvider('TeacherApp');
		
		$dataProvider=new CActiveDataProvider('TeacherApp',array(   
		'criteria' => array(   
        'condition'=>'pass=\'waiting\'',   
        //'param'=>array(':tags'=>$_GET['tags']),   
        //'with'=>array('author'),   
		),   
		'pagination'=>array(   
        'pageSize'=>10,   
        'currentPage'=>0,   
		),   
		)); 
		
		$this->render('confirm',array(
			'dataProvider'=>$dataProvider,
		));
		
	}
	
	public function actionAjax()
	{
		if(Yii::app()->request->isAjaxRequest)
		{
			$id =  (int)Yii::app()->request->getParam('id');
			$pass = Yii::app()->request->getParam('pass');

			$T = TeacherApp::model()->updateByPk($id,$attributes = array('pass' => $pass));

			//if($pass=="yes")//如果是yes，classteacher插入一条记录
			//{
				$teacherApp = TeacherApp::model()->findAllByAttributes(array('id'=>$id));
				$class=new ClassTeacher;
				$class->teacherid=$teacherApp[0]->teacherID;
				$class->classid=$teacherApp[0]->courseID;

				$class->save();

			//}
			
			if($pass=="yes")
			{
				echo "<font color=\"green\">";
			}
			else
			{
				echo "<font color=\"red\">";
			}
			echo $pass;
			echo "</font>";
		}
	}

	public function actionAjaxDelete()
	{
		if(Yii::app()->request->isAjaxRequest)
		{
			$id =  (int)Yii::app()->request->getParam('id');
			$this->loadModel($id)->delete();
			echo "OK";
		}
	}
	
	
	/**
	 * Manages all models.
	 */
	public function actionAdmin()
	{
		$model=new TeacherApp('search');
		$model->unsetAttributes();  // clear any default values
		if(isset($_GET['TeacherApp']))
			$model->attributes=$_GET['TeacherApp'];

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
		$model=TeacherApp::model()->findByPk($id);
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
		if(isset($_POST['ajax']) && $_POST['ajax']==='teacher-app-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
	}
}
