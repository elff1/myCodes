<?php
Yii::import('application.extensions.EDownloadHelper.helpers.EDownloadHelper');//import EDownloadHelper extension
class ResResourceController extends Controller
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
			'accessControl', // perform access control for CRUD operations
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
				'actions'=>array('index','view','search'),
				'users'=>array('@'),
			),
			array('allow', // allow authenticated user to perform 'create' and 'update' actions
				'actions'=>array('create','update'),
				'users'=>array('@'),
			),
			array('allow', // allow admin user to perform 'admin' and 'delete' actions
				'actions'=>array('admin','delete'),
				'users'=>array('@'),
				//'users'=>array('$model->id==$'),
			),
			array('allow',// allow autheneticated user to download the resource
				'actions'=>array('download'),
				'users'=>array('@'),
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

	public function actionSearch()
	{
		$model=new ResResource('search');
		$model->unsetAttributes();  // clear any default values
		
		if(isset($_GET['ResResource'])) 
			$model->attributes=$_GET['ResResource'];

		if (isset($_GET['uid']))//use this for display the owner's resources in 'manage resource' function
		{
			$model->uploader_id=$_GET['uid'];
		}
		
		//only allow to search normal type
		if(Yii::app()->user->type != 3 &&Yii::app()->user->type != 4) 
		{
			$model->resource_type = 'normal';
		}
		$this->render('search',array(
			'model'=>$model,
		));
	}
	
	//function doing save, important interface which will be used in resource, homework, and assignment upload
	static public function saveModel($model, $resType)
    {
     			           
				$resFile = CUploadedFile::getInstance($model, 'path');//get upload file
                $model->path = $resFile;//set it to model
                if(empty($model->path))//no allow for empty path
                {
                    $model->addError('path', 'Path cannot be empty!');
                    return false;
                }
				$model->resource_type= $resType;//set resource type
				$model->upload_time = date('y-m-d H:i:s',time()); //set upload time
				$model->download_count=0;//initial download count set to zero
				$model->uploader_id=Yii::app()->user->id;//set uploader id
				if($model->save())//save model into DB
				{
						if (is_object($resFile) && get_class($resFile) == 'CUploadedFile')
						{
							$resFile->saveAs(Yii::app()->basePath.'/uploads/res/'.Yii::app()->user->id.'+'.$model->path);//save the uploading file to the server
						}	
		                return true;
				}
			
            return false;
	}
	
	/**
	 * Creates a new model.
	 * If creation is successful, the browser will be redirected to the 'view' page.
	 */
	public function actionCreate()
	{
		$model=new ResResource;

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);


		if(isset($_POST['ResResource']))
		{
			$model->attributes=$_POST['ResResource'];//set model's attributes
            if(ResResourceController::saveModel($model, 1))
                $this->redirect(array('view','id'=>$model->id));
		}

		$this->render('create',array(
			'model'=>$model,
		));
	}

	//interface for updating record
	static public function updateModel($model, $id, $resType)
	{
		//if update has a upload file
		if($model->path !='')
		{
				$resFile = CUploadedFile::getInstance($model, 'path');//get upload file
				//set model's attributes
				$model->path = $resFile;
				$model->resource_type= $resType;
				$model->upload_time = date('y-m-d H:i:s',time()); 
				$model->download_count=0;
				$model->uploader_id=Yii::app()->user->id;
				//save model
				if($model->save())
				{
						//save new upload file
						if (is_object($resFile) && get_class($resFile) == 'CUploadedFile')
						{
							$resFile->saveAs(Yii::app()->basePath.'/uploads/res/'.Yii::app()->user->id.'+'.$model->path);
						}	
		                return true;
				}			
		}
		//if update has no upload file
		else
		{
			$oldModel = ResResource::model()->findByPk($id);
			if($model===null)
				throw new CHttpException(404,'The requested page does not exist.');
			$model->path = $oldModel->path;
			$model->resource_type= $resType;
			$model->upload_time = date('y-m-d H:i:s',time()); 
			$model->download_count=0;
			$model->uploader_id=Yii::app()->user->id;
			if ($model->save())
			{
				return true;
			}
		}
		return false;
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
		// resource owner can update his/her resource
		if ($model->uploader_id == Yii::app()->user->id)
		{
			if(isset($_POST['ResResource']))
			{
				$model->attributes=$_POST['ResResource'];
				if(ResResourceController::updateModel($model, $id, 1))
				$this->redirect(array('view','id'=>$model->id));
			}
			$this->render('update',array('model'=>$model,));
		}
		//admin and sysadmin can update the resource
		else if (Yii::app()->user->type == 3 || Yii::app()->user->type == 4) 
		{
			if(isset($_POST['ResResource']))
			{
				$model->attributes=$_POST['ResResource'];
				if(ResResourceController::updateModel($model, $id, 1))
				$this->redirect(array('view','id'=>$model->id));
			}

			$this->render('update',array('model'=>$model,));
		}
		//else, error occured
		else 
		{
			throw new CHttpException(403,
                	'Don\'t do this, baby....., you can only edit your own resource.');
		}
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
			$model = $this->loadModel($id);
			//resource owner can delete his/her resource
			if ($model->uploader_id == Yii::app()->user->id)
			{
            	$model->delete();
            	//if AJAX request (triggered by deletion via admin grid view), we should not redirect the browser	
				if(!isset($_GET['ajax']))
				{
					$this->redirect(isset($_POST['returnUrl']) ? $_POST['returnUrl'] : array('admin', 'uid'=>Yii::app()->user->id));
				}
			}
			//admin and sysadmin can delete resource
			else if (Yii::app()->user->type == 3 || Yii::app()->user->type == 4)
			{
				$model->delete();
            	//if AJAX request (triggered by deletion via admin grid view), we should not redirect the browser	
				if(!isset($_GET['ajax']))
				{
					$this->redirect(isset($_POST['returnUrl']) ? $_POST['returnUrl'] : array('admin', 'uid'=>Yii::app()->user->id));
				}
			}
			//else, throw error
			else 
			{	
				throw new CHttpException(403,
                	'Don\'t do this, baby..... You can only delete resources belonging to you.');
			}

			
		}
		else
			throw new CHttpException(400,'Invalid request. Please do not repeat this request again.');
	}

	/**
	 * Lists all models.
	 */
	//list the resources
	public function actionIndex()
	{
        $conds = array();

        if(isset($_GET['uid'])) {
            array_push($conds,
                'uploader_id='.strval((int)$_GET['uid']));
        }
        //get data
        $dataProvider = new CActiveDataProvider('ResResource', array(
            'criteria' => array('condition' => implode(' and ', $conds))));
		$this->render('index',array(
			'dataProvider'=>$dataProvider,
		));
	}
	/**
	 * Manages all models.
	 */
	public function actionAdmin()
	{
		$model=new ResResource('search');
		$model->unsetAttributes();  // clear any default values
		
		
		if(isset($_GET['ResResource']))
			$model->attributes=$_GET['ResResource'];

		//admin and sysadmin can manage all the resources
		if (Yii::app()->user->type != 3 && Yii::app()->user->type != 4)
		{
			if (isset($_GET['uid']))
			{
				$model->uploader_id=$_GET['uid'];
			}
		}
		$this->render('admin',array(
			'model'=>$model,
		));
	}
	
	//download function
	public function actionDownload()
	{
		$model = new ResResource();
		
	 	if(isset($_GET['id'])) {
	 		$model = $model->findByPk(strval((int)$_GET['id']));
	 		//get path
	 		$serverPath = '/uploads/res/'.$model->uploader_id.'+'.$model->path;
	 		if(!file_exists($serverPath))//if the file doesn't exist on the server, error occur
	 		{
	 			throw new CHttpException(404,'File Not Found on the Server.');
	 			return ;
	 		}
	 		$model->download_count++;//download count +1
	 		if ($model->save())//update record in DB
	 		{
	 			//call EDownloadHelper to start download
	 			EDownloadHelper::download(Yii::app()->basePath.'/uploads/res/'.$model->uploader_id.'+'.$model->path);
	 		}
        }
	}

	/**
	 * Returns the data model based on the primary key given in the GET variable.
	 * If the data model is not found, an HTTP exception will be raised.
	 * @param integer the ID of the model to be loaded
	 */
	public function loadModel($id)
	{
		$model=ResResource::model()->findByPk($id);
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
		if(isset($_POST['ajax']) && $_POST['ajax']==='res-resource-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
	}
	
	private function getExtName($fileName)//get files' extension name
	{
		if(empty($fileName))
		{
			return false;
		}
		else 
		{
			$fileName = strtolower($fileName);
			$revStr = strrev($fileName);
			$extLen = strpos($revStr, '.');
			$fileNameLen = strlen($fileName);
			$extName  = substr($fileName, $fileNameLen - $extLen);
			
			return $extName;
		}
	}
	
	//function for delete comment
	public static function onDeleteComment($event)
	{
		if(!$event->comment->delete())
		{
			throw new CHttpException(404,'Comments Deletion Failed!');
		}
	}
	
	//function for create new comment
	public static function onNewComment($event)
	{
		$commentModel = new Comments;
		
		/*$resComModel = new ResComments;
		$resComModel->resId = $event->commentedModel->id;
		$resComModel->commentId = $event->comment->id;*/
	}
}
