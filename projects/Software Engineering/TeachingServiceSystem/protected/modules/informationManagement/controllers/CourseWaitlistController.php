<?php
//课程申请控制类
class CourseWaitlistController extends Controller
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
			array('deny',  // deny all users
				'users'=>array('*'),
			),
		);
	}

	/**
	 * Displays a particular model.
	 * @param integer $id the ID of the model to be displayed
	 */
	 //列出课程申请
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
	 
	 //创建
	public function actionCreate()
	{
		$model=new CourseWaitlist;

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);

		if(isset($_POST['CourseWaitlist']))
		{
			$model->attributes=$_POST['CourseWaitlist'];
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
	 //更新
	public function actionUpdate($id)
	{
		$model=$this->loadModel($id);

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);

		if(isset($_POST['CourseWaitlist']))
		{
			$model->attributes=$_POST['CourseWaitlist'];
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
	 //删除
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
	 //列出所有
	public function actionIndex()
	{
		$dataProvider=new CActiveDataProvider('CourseWaitlist');
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
		
		$dataProvider=new CActiveDataProvider('CourseWaitList',array(   
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

			$T = CourseWaitList::model()->updateByPk($id,$attributes = array('pass' => $pass));

			if($pass=="yes")//如果是yes，classteacher插入一条记录
			{
				$courseWaitList = CourseWaitList::model()->findAllByAttributes(array('id'=>$id));
				$course=new CourseBasicInfo;
				$course->course_id=$courseWaitList[0]->id;
				$course->name=$courseWaitList[0]->name;
				$course->credit=$courseWaitList[0]->credit;
				$course->class=$courseWaitList[0]->class;
				$course->prerequsite_required=$courseWaitList[0]->prerequsite_required;
				$course->introduction=$courseWaitList[0]->introduction;
				$course->syllabus=$courseWaitList[0]->syllabus;
				$course->department_id=$courseWaitList[0]->department_id;
				$course->priority=$courseWaitList[0]->priority;
				$course->save();
			}
			
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
	 //管理申请
	public function actionAdmin()
	{
		$model=new CourseWaitlist('search');
		$model->unsetAttributes();  // clear any default values
		if(isset($_GET['CourseWaitlist']))
			$model->attributes=$_GET['CourseWaitlist'];

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
		$model=CourseWaitlist::model()->findByPk($id);
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
		if(isset($_POST['ajax']) && $_POST['ajax']==='course-waitlist-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
	}
}
