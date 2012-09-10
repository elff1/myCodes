<?php

class QuestionBankController extends Controller
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
				'actions'=>array('create','update','delete'),
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

	/**
	 * Creates a new model.
	 * If creation is successful, the browser will be redirected to the 'view' page.
	 */
	public function actionCreate()
	{
		$model=new QuestionBank;

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);

		if(isset($_POST['QuestionBank']))
		{
			$tmparray = $_POST['QuestionBank'];
			//TODO
			// get the teacher id from account component		
			$tmparray['teacher_id']  = AccountComponent::getSelected_Teacher_id();
			// get the course id from account component			
			$tmparray['course_id'] = AccountComponent::getSelected_course_id();

			// if the question type is judge, no selection is needed.
			if ($tmparray['type'] == 1) {
				$tmparray['selection_a']='null';
				$tmparray['selection_b']='null';
				$tmparray['selection_c']='null';
				$tmparray['selection_d']='null';

			}
			$model->attributes= $tmparray;
			// save model
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

		if(isset($_POST['QuestionBank']))
		{
			// get data from post
			$model->attributes=$_POST['QuestionBank'];
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
		//TODO
		// get the teacher id and course id
		$teacher_id = AccountComponent::getSelected_Teacher_id();
		$course_id = AccountComponent::getSelected_course_id();

		// get the data filtered by teacher id and course id
		$dataProvider=new CActiveDataProvider(
			'QuestionBank',
			array(
				'criteria'=>array(
					'condition' => "teacher_id = $teacher_id and course_id = $course_id"
				)
			)
		
		);
		// render
		$this->render('index',array(
			'dataProvider'=>$dataProvider,
		));
	}

	/**
	 * Manages all models.
	 */
	public function actionAdmin()
	{
		$model=new QuestionBank('search');
		$model->unsetAttributes();  // clear any default values
		if(isset($_GET['QuestionBank']))
			$model->attributes=$_GET['QuestionBank'];
		//TODO
		// get the data filtered by teacher id and course id
		$teacher_id = AccountComponent::getSelected_Teacher_id();
		$course_id = AccountComponent::getSelected_course_id();

		// filter using teacher id and course id
		$criteria = new CDbCriteria;
		$criteria->condition="teacher_id = $teacher_id and course_id = $course_id";
		$model->setDbCriteria($criteria);

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
		$model=QuestionBank::model()->findByPk($id);
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
		if(isset($_POST['ajax']) && $_POST['ajax']==='question-bank-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
	}

	public function actionDynamicAnswer($type)
	{
		// dynamicly change the option tag according to the type of question.
		if ($type==0)
        {
            echo CHtml::tag('option',array('value'=>'A'),CHtml::encode('A'),true);
			echo CHtml::tag('option',array('value'=>'B'),CHtml::encode('B'),true);
			echo CHtml::tag('option',array('value'=>'C'),CHtml::encode('C'),true);
            echo CHtml::tag('option',array('value'=>'D'),CHtml::encode('D'),true);			
		}
		if ($type==1)
        {
            echo CHtml::tag('option',array('value'=>'T'),CHtml::encode('T'),true);
            echo CHtml::tag('option',array('value'=>'F'),CHtml::encode('F'),true);
		}		
	}

	public function actionBatchCreate()
	{
		//$model = new SystemAdminBasicInfoBatchForm();
		
		// uncomment the following code to enable ajax-based validation
		/*
		if(isset($_POST['ajax']) && $_POST['ajax']==='basicSystemAdminInfo-batch-form-batchCreate-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
		 */


		$model = new QuestionBatchForm();
		if(isset($_POST['QuestionBatchForm']))
		{
			$model->file=CUploadedFile::getInstance($model,'file');
// get the uploaded file
			if($model->validate())
			{
				$transaction =  PersonalInfo::model()->dbConnection->beginTransaction();
				try{
					if(($fp = fopen($model->file->tempName,'r'))!==FALSE){
						setlocale(LC_ALL, 'en_US.UTF-8');//set locale so that correct encoding is guaranteed.
						while(($data = fgetcsv($fp))!==FALSE){//loop the input file
							$num = count($data);
							echo $num;
//	read 7 string s from csv
							if($num != 7){
								continue;
							}
// create new question bank							
							$newQuestionBank = new QuestionBank;
							$newQuestionBank->batchSetAttributes($data);
// save to database							
							$newQuestionBank->save();
						}	
						setlocale(LC_ALL, null);//return to default
// commit the transaction						
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
					throw $e;
				}
			}
		}
// 		if(isset ($_FILES["file"]["error"]))
// 		{
// 			if ($_FILES["file"]["error"]>0) {
// 				echo 'Error';
// 				$this->render('batchCreate');
// 				return;
// 			}
// 			$filename=$_FILES["file"]["tmp_name"];
// 			$fp=fopen($filename,"r");			
// 			$transaction =  QuestionBank::model()->dbConnection->beginTransaction();
// 			try{
// 				if(($fp = fopen($filename,"r"))!==FALSE){
// 					setlocale(LC_ALL, 'en_US.UTF-8');//set locale so that correct encoding is guaranteed.
// 					while(($data = fgetcsv($fp))!==FALSE){//loop the input file
// 						$num = count($data);
// 						echo $num;
// 						if($num != 7){
// 							continue;
// 						}
// 						for ($i=0;$i<7;$i++) {
// 							echo $data[$i]."<br>";
// 						}
// 						$newQuestionBank = new QuestionBank;
// 						$newQuestionBank->batchSetAttributes($data);
// 						$newQuestionBank->save();
// 					}	
// 					setlocale(LC_ALL, null);//return to default
// 					$transaction->commit();
// 					$this->redirect(array('admin'));
// 				} else {
// 					throw new Exception('File reading error');
// 				}
// 			}
// 			catch(Exception $e)
// 			{
// 				$transaction->rollBack();
// 				setlocale(LC_ALL, null); //set back locale
// 				throw $e;
// 			}
			
// 		}
		
		$this->render('batchCreate',array('model'=>$model));
	}
}
