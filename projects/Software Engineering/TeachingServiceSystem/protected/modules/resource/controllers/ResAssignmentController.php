<?php

require('ResResourceController.php');

class ResAssignmentController extends Controller
{

    private $_teachingclass = null;
    private $_teacher = null;

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
            'classContext + create + index + admin', // check to ensure valid class context
            //'rightStudent + index + view',
            // check to ensure the right teacher
            'beTeacher + create + update + admin + delete',
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
        $model = $this->loadModel($id);
        $u_type = Yii::app()->user->type
        if ($u_type == UserAuthentication::TYPE_STUDENT){
            // only the student in the class can view the assignment
            $this->rightStudent($model->teachingclass_id);  
        } else if ($u_type == UserAuthentication::TYPE_TEACHER) {
            // Only the teacher teach the class can view the assignment 
            $this->rightTeacher($model->teachingclass_id);
        }
        // load the related resource
        $res_model = ResResource::model()->findbyPk($model->resource_id);
		$this->render('view',array(
            'model'=>$model,
            'res_model'=>$res_model,
		));
	}

	/**
	 * Creates a new model.
	 * If creation is successful, the browser will be redirected to the 'view' page.
	 */
	public function actionCreate()
	{
        // only the teacher teach the class can create an assignment
        $this->rightTeacher($this->_teachingclass->id);
		$model=new ResAssignment;
        $res_model = new ResResource;

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);
        $flag = false;
		if(isset($_POST['ResAssignment']))
		{
            // filter user input
            require('PurifierOptions.php');
            $purifier = new CHtmlPurifier();
            $purifier->options = $p_options;
			$model->attributes=$_POST['ResAssignment'];
            $model->teachingclass_id = $this->_teachingclass->id;
            $model->teacher_id = $this->_teacher->id;
            $model->requirement = $purifier->purify($model->requirement);
            // save resource
            if(isset($_POST['ResResource']))
            {
                $res_model->attributes = $_POST['ResResource'];
                $flag = ResResourceController::saveModel($res_model, 3);
                $model->resource_id = $res_model->id;
            }

			if($model->save() && $flag)
				$this->redirect(array('view','id'=>$model->id));
		}

		$this->render('create',array(
			'model'=>$model,
            'res_model'=>$res_model,
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
        $res_model = ResResource::model()->findbyPk($model->resource_id);
        // filter users
        if (Yii::app()->user->type == UserAuthentication::TYPE_STUDENT) {
            $this->rightStudent($model->teachingclass_id);
        } else if (Yii::app()->user->type == UserAuthentication::TYPE_TEACHER) {
            $this->rightTeacher($model->teachingclass_id);
        }

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);
        $flag = false;
		if(isset($_POST['ResAssignment']))
        {
            // filter user input
            require('PurifierOptions.php');
            $model->attributes=$_POST['ResAssignment'];
            $purifier = new CHtmlPurifier();
            $purifier->options = $p_options;
            $model->requirement = $purifier->purify($model->requirement);
            if (isset($_POST['ResResource'])) {
                $res_model->attributes = $_POST['ResResource'];
                $flag = ResResourceController::updateModel($res_model, $model->resource_id, 3);
            }

			if($model->save() && $flag)
				$this->redirect(array('view','id'=>$model->id));
		}
		$this->render('update',array(
			'model'=>$model,
            'res_model'=>$res_model,
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
            $model = $this->loadModel($id);
            $this->rightTeacher($model->teachingclass_id);
            if (count($model->resHomeworks) > 0) {
                throw new CHttpException(400, 'You cannot delete an Assignment which alread has homework');
            }
			$model->delete();
            // delete the related resource
            ResResource::model()->findbyPk($model->resource_id)->delete();

			// if AJAX request (triggered by deletion via admin grid view), we should not redirect the browser
			if(!isset($_GET['ajax']))
				$this->redirect(isset($_POST['returnUrl']) ? $_POST['returnUrl'] : array('admin', 'teachingclass_id'=>$model->teachingclass_id));
		}
		else
			throw new CHttpException(400,'Invalid request. Please do not repeat this request again.');
	}

	/**
	 * Lists all models.
	 */
	public function actionIndex()
	{
        $conds = array();
        array_push($conds, 'teachingclass_id='.strval($this->_teachingclass->id));
        $u_type = Yii::app()->user->type;
        // use get parameters as filters
        if($u_type == UserAuthentication::TYPE_STUDENT) {
            // hide not published assignments from students
            $this->rightStudent($this->_teachingclass->id);
            array_push($conds, 'is_published=1');
        } else if ($u_type == UserAuthentication::TYPE_TEACHER) {
            $this->rightTeacher($this->_teachingclass->id);
        }
        if(isset($_GET['teachingclass_id'])) {
            array_push($conds, 'teachingclass_id='
                .strval((int)$_GET['teachingclass_id']));
        }
        if(isset($_GET['student_id'])) {
            array_push($conds,
                'student_id='.strval((int)$_GET['student_id']));
        }
        // search the assignment
        $dataProvider = new CActiveDataProvider('ResAssignment', array(
            'criteria' => array('condition' => implode(' and ', $conds)),
            'pagination'=>array(
                'pageSize'=>4,
            ),
        ));
		$this->render('index',array(
			'dataProvider'=>$dataProvider,
		));
	}

	/**
	 * Manages all models.
	 */
	public function actionAdmin()
	{
        // only the teacher teach the class can view the page
        if (Yii::app()->user->type ==  UserAuthentication::TYPE_TEACHER)
            $this->rightTeacher($this->_teachingclass->id);
		$model=new ResAssignment('search');
		$model->unsetAttributes();  // clear any default values
        // load params
		if(isset($_GET['ResAssignment']))
			$model->attributes=$_GET['ResAssignment'];
        if(isset($_GET['teachingclass_id']))
            $model->teachingclass_id=$_GET['teachingclass_id'];

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
		$model=ResAssignment::model()->findByPk($id);
		if($model===null)
			throw new CHttpException(404,'The requested page does not exist.');
		return $model;
	}

    /**
     * Called before the actionCreate() action method to ensure a proper
     * class context.
     */
    public function filterClassContext($filterChain)
    {
        $teachingclassId = null;
        if(isset($_GET['teachingclass_id'])){
            $teachingclassId = $_GET['teachingclass_id'];
        } else if(isset($_POST['teachingclass_id'])){
            $teachingclassId = $_POST['teachingclass_id'];
        }
        $this->loadTeachingclass($teachingclassId);
                
        $filterChain->run();
    }

    /**
     * The teacher must teach the class
     */
    public function rightTeacher($class_id)
    {
        $teacherId = Yii::app()->user->id;
        $this->loadTeacher($teacherId);
        $exists = ClassTeacher::model()->exists(
            'classid=:cid and teacherid=:tid',
            array(':cid'=>$class_id,
            ':tid'=>$this->_teacher->id));
        if (!$exists) {
            throw new CHttpException(403,
                'You are not teaching this class');
        }
    }
    /**
     * Should be teacher 
     */
    public function filterBeTeacher($filterChain)
    {
        if (Yii::app()->user->type == UserAuthentication::TYPE_STUDENT) {
            throw new CHttpException(403, '=w=');
        }
        $filterChain->run();
    }

    /**
     * ensure the student in the class
     */ 
    public function rightStudent($class_id)
    {
        if (Yii::app()->user->type == UserAuthentication::TYPE_STUDENT) {
            if (!CourseSelSched::model()->exists(
                'class_id=:cid and stu_id=:sid',
                array(':cid'=>$class_id,
                ':sid'=>Yii::app()->user->id))) {
                    throw new CHttpException(403,
                        'You are not taking this class');
            }
        }
    }
    /**
     * load the class
     */ 
    protected function loadTeachingclass($teachingclass_id)
    {
        if($this->_teachingclass == null){
            $this->_teachingclass = TeachingclassInfo::model()->findbyPk($teachingclass_id);
            if($this->_teachingclass == null){
                throw new CHttpException(404,
                    'The request teachingclass does not exist.');
            }
        }
        return $this->_teachingclass;
    }

    /**
     * load the related teacher 
     */
    protected function loadTeacher($teacher_id){
        if($this->_teacher == null){
            $this->_teacher = TeacherBasicInfo::model()->
                findbyPk($teacher_id);
            if($this->_teacher == null){
                throw new CHttpException(404,
                    'The request teacher does not exist.');
            }
        }
        return $this->_teacher;
    }


	/**
	 * Performs the AJAX validation.
	 * @param CModel the model to be validated
	 */
	protected function performAjaxValidation($model)
	{
		if(isset($_POST['ajax']) && $_POST['ajax']==='res-assignment-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
	}
}
