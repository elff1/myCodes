<?php
//个人信息控制器
class PersonalInfoController extends Controller
{
	//根据省份，动态ajax改变城市列表
	public function actionDynamicCity($pid)
	{
		$models = PersonalInfo::model()->getCityList($pid);
        foreach($models as $value=>$name)
        {
            echo CHtml::tag('option',array('value'=>$value),CHtml::encode($name),true);
        }
	}
	
	public function checkUpdate($pid){
		if(Yii::app()->user->isGuest){
			return false;
		}
		$userType = Yii::app()->user->type; 
		return ($userType==UserAuthentication::TYPE_SYSTEM_ADMIN) ||
		($userType==UserAuthentication::TYPE_ADMIN) || 
		(Yii::app()->user->personalInfoID==$pid); 
	}
	

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
				'actions'=>array('create','update','dynamicCity'),
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
	 //查看
	public function actionView($id)
	{
		$this->render('view',array(
			'model'=>$this->loadModel($id),
		));
	}


	
	public function actionBatchCreate()//由于目前 personalInfo 永远都和某个user绑定，故这个batchCreate只是测试之用。
	{
		$model = new PersonalInfoBatchForm();
		
		// uncomment the following code to enable ajax-based validation
		/*
		if(isset($_POST['ajax']) && $_POST['ajax']==='personalInfo-batch-form-batchCreate-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
		*/
		
		if(isset($_POST['PersonalInfoBatchForm']))
		{
			$model->file=CUploadedFile::getInstance($model,'file');
			if($model->validate())
			{
				$transaction =  PersonalInfo::model()->dbConnection->beginTransaction();
				try{
					if(($fp = fopen($model->file->tempName,'r'))!==FALSE){
						setlocale(LC_ALL, 'en_US.UTF-8');//set locale so that correct encoding is guaranteed.
						while(($data = fgetcsv($fp))!==FALSE){//loop the input file
							$num = count($data);
							if($num != 17){
								throw new Exception('File reading error');
							}
							$newRecord = new PersonalInfo;
							$newRecord->batchSetAttributes($data);
							if(!$newRecord->save()){
								throw new Exception('File reading error');
							}
							
							if(!empty($newRecord->photo)){
								$file = Yii::app()->file->set($newRecord->tempImagePath);
								$file->move($newRecord->imageDir.'/'.$newRecord->photo);
							}
						}
						setlocale(LC_ALL, null);//return to default
						$transaction->commit();
						$this->redirect(array('admin'));
					} else {
						throw new Exception('File reading error');
					}
				}
				catch(Exception $e)
				{
					$transaction->rollBack();
					setlocale(LC_ALL, null); //set back locale
					$model->addError('file',
					Yii::t('personalInfo','{attribute} Invalid file format.'
					,array('{attribute}'=>$model->getAttributeLabel('file'),)));
				}
			}
		}
		
		$this->render('batchCreate',array('model'=>$model));
	}




	/**
	 * Creates a new model.
	 * If creation is successful, the browser will be redirected to the 'view' page.
	 */
	 //添加
	public function actionCreate()
	{
		$model=new PersonalInfo;

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);

		if(isset($_POST['PersonalInfo']))
		{
			$model->attributes=$_POST['PersonalInfo'];
			$model->setPhotoPath();
			
			if($model->save()){
				if($model->image!==null){
					$model->image->saveAs($model->imageDir.'/'.$model->photo);
				}
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
	 //更新
	public function actionUpdate($id)
	{
		$model=$this->loadModel($id);

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);

		if(isset($_POST['PersonalInfo']))
		{
			$model->attributes=$_POST['PersonalInfo'];
			$oldPhotoPath = $model->photo;
			$model->setPhotoPath();
			
			if($model->save()){
				$model->updatePhoto($oldPhotoPath);
				$this->redirect(array('view','id'=>$model->id));
			}
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
	public function actionIndex()
	{
		$dataProvider=new CActiveDataProvider('PersonalInfo');
		$this->render('index',array(
			'dataProvider'=>$dataProvider,
		));
	}

	/**
	 * Manages all models.
	 */
	public function actionAdmin()
	{
		$model=new PersonalInfo('search');
		$model->unsetAttributes();  // clear any default values
		if(isset($_GET['PersonalInfo']))
			$model->attributes=$_GET['PersonalInfo'];

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
		$model=PersonalInfo::model()->findByPk($id);
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
		if(isset($_POST['ajax']) && $_POST['ajax']==='personal-info-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
	}
}
