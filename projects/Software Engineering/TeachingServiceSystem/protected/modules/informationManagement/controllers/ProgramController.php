<?php
//培养方案控制器
class ProgramController extends Controller
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
	 //显示
	public function actionView($id)
	{
		$model = $this->loadModel($id);
		//该培养方案下的课程
		$courseDataProvider=new CArrayDataProvider($model->programDetails, array(
    		'sort'=>array(
        		'attributes'=>array(
             		'course_id','type','recommended_year','required',
             	),
        	),
        	'pagination'=>array(
        		'pageSize'=>10,
    		),
		));
		
		$this->render('view',array(
			'model'=>$this->loadModel($id),
			'courseDataProvider'=>$courseDataProvider,
		));
	}

	/**
	 * Creates a new model.
	 * If creation is successful, the browser will be redirected to the 'view' page.
	 */
	 //创建
	public function actionCreate()
	{
		$model=new Program;

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);

		if(isset($_POST['Program']))
		{
			$model->attributes=$_POST['Program'];
			if($model->save())
				$this->redirect(array('view','id'=>$model->id));
		}

		$this->render('create',array(
			'model'=>$model,
		));
	}
	
	//批量创建
	public function actionBatchCreate()
	{
		$model=new ProgramBatchForm;
	
		// uncomment the following code to enable ajax-based validation
		/*
		if(isset($_POST['ajax']) && $_POST['ajax']==='program-batch-form-batchCreate-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
		*/
		
		if(isset($_POST['ProgramBatchForm']))
		{
			$model->file=CUploadedFile::getInstance($model,'file');//获取文件
			if($model->validate())//model 通过验证
			{
				//开始事务，读取csv，保存
				$transaction =  Program::model()->dbConnection->beginTransaction();
				try{
					if(($fp = fopen($model->file->tempName,'r'))!==FALSE){
						setlocale(LC_ALL, 'en_US.UTF-8');//set locale so that correct encoding is guaranteed.
						while(($data = fgetcsv($fp))!==FALSE){//loop the input file
							$num = count($data);
							if($num != 5 || $data[0]===null){ //error for empty string as well
								throw new Exception('File reading error');
							}
							$newRecord = new Program;
							$newRecord->name = trim($data[0]); //strip leading and trailing whitespace characters
							$newRecord->department_id = trim($data[1]);
							$newRecord->length = trim($data[2]);
							$newRecord->grade = trim($data[3]);
							$newRecord->introduction = trim($data[4]);
							if(!$newRecord->save()){
								throw new Exception('File reading error');
							}
						}
						setlocale(LC_ALL, null);//return to default
						$transaction->commit();
						$this->redirect(array('admin'));
					} else {//回滚 
						throw new Exception('File reading error');
					}
				}
				catch(Exception $e)
				{
					$transaction->rollBack();
					setlocale(LC_ALL, 'en_US.UTF-8');
					$model->addError('file',
					Yii::t('program','{attribute} Invalid file format.'
					,array('{attribute}'=>$model->getAttributeLabel('file'),)));
				}
			}
		}
		//所有学院的id与name
		$departmentDataProvider=new CArrayDataProvider(Department::model()->findAll(), array(
    		'sort'=>array(
        		'attributes'=>array(
             		'id',
             	),
        	),
        	'pagination'=>array(
        		'pageSize'=>5,
    		),
		));
		
		$this->render('batchCreate',array('model'=>$model,
		'departmentDataProvider'=>$departmentDataProvider));
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

		if(isset($_POST['Program']))
		{
			$model->attributes=$_POST['Program'];
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
		$dataProvider=new CActiveDataProvider('Program');
		$this->render('index',array(
			'dataProvider'=>$dataProvider,
		));
	}

	/**
	 * Manages all models.
	 */
	 //管理
	public function actionAdmin()
	{
		$model=new Program('search');
		$model->unsetAttributes();  // clear any default values
		if(isset($_GET['Program']))
			$model->attributes=$_GET['Program'];

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
		$model=Program::model()->findByPk($id);
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
		if(isset($_POST['ajax']) && $_POST['ajax']==='program-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
	}
	
}
