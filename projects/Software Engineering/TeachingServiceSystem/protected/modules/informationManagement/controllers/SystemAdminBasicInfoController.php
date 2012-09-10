<?php
//系统管理员基本信息控制器
class SystemAdminBasicInfoController extends Controller
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
	//在事务中使用，创建一个管理员
	private function createSingleSystemAdmin($model, $personalInfoModel, $batchMode = false){//used within a transaction.
		$userModel = new UserAuthentication;
		$userModel->password = $model->system_admin_id;
		$userModel->type = UserAuthentication::TYPE_SYSTEM_ADMIN;
		//保存 UserAuthentication
		if(!$userModel->save()){
			throw new Exception('UserAuthentication save error');
		}
		
		$model->id = $userModel->id;
		//保存personalInfo
		if(!$personalInfoModel->save()){
			throw new Exception('PersonalInfo save error');
		}
		//保存图片
		if(!$batchMode && ($personalInfoModel->image!==null)){
			$personalInfoModel->image->saveAs($personalInfoModel->imageDir.'/'.$personalInfoModel->photo);
		}
		
		if($batchMode && !empty($personalInfoModel->photo)){
			$file = Yii::app()->file->set($personalInfoModel->tempImagePath);
			$file->move($personalInfoModel->imageDir.'/'.$personalInfoModel->photo);
		}
		//链接 personal_info_id
		$model->personal_info_id = $personalInfoModel->id;
		//保存 SystemAdminBasicInfo
		if(!$model->save()){
			throw new Exception('SystemAdminBasicInfo save error');
		}
		//赋权限
		Rights::assign('SystemAdmin', $userModel->id);
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
		//two models for input
		$model=new SystemAdminBasicInfo;
		$personalInfoModel = new PersonalInfo;
		
		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);
		// POST 提交了
		if(isset($_POST['SystemAdminBasicInfo']) && isset($_POST['PersonalInfo']) )
		{
			$model->attributes=$_POST['SystemAdminBasicInfo'];
			$personalInfoModel->attributes = $_POST['PersonalInfo'];
			$personalInfoModel->setPhotoPath();
			// 修改数据库的 transaction
			if($model->validate() && $personalInfoModel->validate()){
				$transaction = SystemAdminBasicInfo::model()->dbConnection->beginTransaction();
				try{
					$this->createSingleSystemAdmin($model, $personalInfoModel);
					$transaction->commit();
					$this->redirect(array('view','id'=>$model->id));
				} 
				catch(Exception $e){
					$transaction->rollBack();
					//don't know what error to say.
				}
			}
		}
		$this->render('create',array(
			'model'=>$model,
			'personalInfoModel'=>$personalInfoModel,
		));
	}
	//批量创建
	public function actionBatchCreate()
	{
		$model = new SystemAdminBasicInfoBatchForm();
		
		// uncomment the following code to enable ajax-based validation
		/*
		if(isset($_POST['ajax']) && $_POST['ajax']==='basicSystemAdminInfo-batch-form-batchCreate-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
		*/
		
		if(isset($_POST['SystemAdminBasicInfoBatchForm']))
		{
			$model->file=CUploadedFile::getInstance($model,'file');
			if($model->validate())
			{	//事务.for循环
				$transaction =  SystemAdminBasicInfo::model()->dbConnection->beginTransaction();
				try{
					if(($fp = fopen($model->file->tempName,'r'))!==FALSE){
						setlocale(LC_ALL, 'en_US.UTF-8');//set locale so that correct encoding is guaranteed.
						while(($data = fgetcsv($fp))!==FALSE){//loop the input file
						//读取csv
							$num = count($data);

							if($num != 18){
								throw new Exception('File reading error');
							}
							
							$newSystemAdminBasicInfo = new SystemAdminBasicInfo;
							$newPersonalInfo = new PersonalInfo;
							//设置属性
							$newSystemAdminBasicInfo->batchSetAttributes(array_slice($data, 0, 1));
							$newPersonalInfo->batchSetAttributes(array_slice($data, 1, 17));
							//保存
							$this->createSingleSystemAdmin($newSystemAdminBasicInfo, $newPersonalInfo, true);
							
						}	
						setlocale(LC_ALL, null);//return to default
						$transaction->commit();
						$this->redirect(array('admin'));
					} else {
						throw new Exception('File reading error');
					}
				}
				catch(Exception $e)
				{//回滚
					$transaction->rollBack();
					setlocale(LC_ALL, null); //set back locale
					$model->addError('file',
					Yii::t('user','{attribute} Invalid file format.'
					,array('{attribute}'=>$model->getAttributeLabel('file'),)));
				}
			}
		}
		
		$this->render('batchCreate',array('model'=>$model));
	}

	/**
	 * Updates a particular model.
	 * If update is successful, the browser will be redirected to the 'view' page.
	 * @param integer $id the ID of the model to be updated
	 */
	public function actionUpdate($id)
	{
		$model=$this->loadModel($id);
		$personalInfoModel=PersonalInfo::model()->findByPk($model->personal_info_id);

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);
		//更新
		if(isset($_POST['SystemAdminBasicInfo']) && isset($_POST['PersonalInfo']) )
		{
			$model->attributes=$_POST['SystemAdminBasicInfo'];
			$personalInfoModel->attributes = $_POST['PersonalInfo'];
			$oldPhotoPath = $personalInfoModel->photo;
			$personalInfoModel->setPhotoPath();
			//事务
			if($model->validate() && $personalInfoModel->validate()){
				$transaction = SystemAdminBasicInfo::model()->dbConnection->beginTransaction();
				try{
					$model->save();
					$personalInfoModel->save();
					$personalInfoModel->updatePhoto($oldPhotoPath);
					$transaction->commit();
					$this->redirect(array('view','id'=>$model->id));
				}
				catch(Exception $e){
					$transaction->rollBack();
					//don't know what error to say.
				}
			}
		}

		$this->render('update',array(
			'model'=>$model, 'personalInfoModel'=>$personalInfoModel,
		));
	}

	/**
	 * Deletes a particular model.
	 * If deletion is successful, the browser will be redirected to the 'admin' page.
	 * @param integer $id the ID of the model to be deleted
	 */
	public function actionDelete($id)
	{
		if(Yii::app()->request->isPostRequest) //delete 3 models & revoke assignment
		{
			// we only allow deletion via POST request
			//transaction 分步删除
			$transaction = SystemAdminBasicInfo::model()->dbConnection->beginTransaction();
			try {
				$model = $this->loadModel($id);
				$userModel = UserAuthentication::model()->findByPk($model->id);
				$personalInfoModel = PersonalInfo::model()->findByPk($model->personal_info_id);
				
				assert($userModel!==null && $personalInfoModel !==null);
				
				//去除权限
				Rights::revoke('SystemAdmin', $userModel->id);
				$userModel->delete();
				$personalInfoModel->delete();
				$transaction->commit();
			}
			catch(Exception $e){
				$transaction->rollBack();
				//don't know what error to say.
			}

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
		$dataProvider=new CActiveDataProvider('SystemAdminBasicInfo');
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
		$model=new SystemAdminBasicInfo('search');
		$model->unsetAttributes();  // clear any default values
		if(isset($_GET['SystemAdminBasicInfo']))
			$model->attributes=$_GET['SystemAdminBasicInfo'];

		$this->render('admin',array(
			'model'=>$model,
		));
	}

	/**
	 * Returns the data model based on the primary key given in the GET variable.
	 * If the data model is not found, an HTTP exception will be raised.
	 * @param integer the ID of the model to be loaded
	 */
	 //载入
	public function loadModel($id)
	{
		$model=SystemAdminBasicInfo::model()->findByPk($id);
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
		if(isset($_POST['ajax']) && $_POST['ajax']==='system-admin-basic-info-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
	}
}
