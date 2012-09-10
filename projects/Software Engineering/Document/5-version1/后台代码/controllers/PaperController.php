<?php

class PaperController extends Controller
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
		$model=new Paper;

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);

		if(isset($_POST['Paper']))
		{
			$model->attributes=$_POST['Paper'];
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

		if(isset($_POST['Paper']))
		{
			$model->attributes=$_POST['Paper'];
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
		$dataProvider=new CActiveDataProvider('Paper');
		$this->render('index',array(
			'dataProvider'=>$dataProvider,
		));
	}

	/**
	 * Manages all models.
	 */
	public function actionAdmin()
	{
		$model=new Paper('search');
		$model->unsetAttributes();  // clear any default values
		if(isset($_GET['Paper']))
			$model->attributes=$_GET['Paper'];

		$this->render('admin',array(
			'model'=>$model,
		));
	}

	/**
	* Manually generate paper questions
	*/
	public function actionAddQuestions()
	{
		// echo "addQustion<br />";
		if(isset($_POST['someChecks']))
		{
			// get the selected questions array
			$selected=$_POST['someChecks'];
			$paper_id = AccountComponent::getSelected_paper_id();
			// add the question into the database one by one
			foreach($selected as $i) {
				// echo $i; echo "<br />";
				$model=new Paper;
				$model->paper_id = $paper_id;
				$model->pro_id = $i;
				$model->pro_score = 5;
				$model->save();
			}
		}

		$this->redirect(array('admin'));
	}
	
	/**
	* Auto generate paper questions
	*/
	public function actionAutoAdd() {
 		$model1=new AutoAdd;
 		if(isset($_POST['AutoAdd']))
 		{
 			$model1->attributes=$_POST['AutoAdd'];
 			if($model1->validate())
 			{
 				// get the question nubmer
 				$number=$model1->number;
 				$paper_id = AccountComponent::getSelected_paper_id();
 				// add the question into the database one by one
 				for ($i = 0; $number > $i; $i=$i+1) {
 					$questions = PaperBankController::getUnusedQuestionsID();
 					$question = $questions[array_rand($questions, 1)];
 					// echo $question; echo "<br />";
 					$model=new Paper;
 					$model->paper_id = $paper_id;
 					$model->pro_id = $question;
 					$model->pro_score = 5;
 					$model->save();
 				}
 				$this->redirect(array('paperBank/view','id'=>$paper_id));
 			}
 		}
	}

	/**
	 * Get the selected paper's problem's ID
	 * @return the selected probleam's ID
	 */
	public static function getSelectedPaperProID($paper_id,$pro_id){
		$models=Paper::model()->findAllByAttributes(array('paper_id'=>$paper_id,'pro_id'=>$pro_id));
		$ids=CHtml::listData($models,'id','id');
		return end($ids);
	}
	/**
	 * Returns the data model based on the primary key given in the GET variable.
	 * If the data model is not found, an HTTP exception will be raised.
	 * @param integer the ID of the model to be loaded
	 */
	public function loadModel($id)
	{
		$model=Paper::model()->findByPk($id);
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
		if(isset($_POST['ajax']) && $_POST['ajax']==='paper-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
	}
}
