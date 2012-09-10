<?php
require('ResResourceController.php');

class ResHomeworkController extends Controller
{
    private $_student = null;
    private $_teacher = null;
    private $_teachingclass = null;
    private $_assignment = null;
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
            'classContext + index + admin', // check to ensure valid class context
            'assignmentContext + create',
            'beStudent + create', // check to ensure student in class
            // check to ensure the homework belongs to some assignment
            // check to ensure the teacher teach the class
            'beTeacher + admin',
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
        $u_type = Yii::app()->user->type;
        if ($u_type==UserAuthentication::TYPE_STUDENT 
            && $model->student_id!=Yii::app()->user->id) {
            // student can only view his own homework
            throw new CHttpException(403, "Can't view the homework");
        } else if ($u_type == UserAuthentication::TYPE_TEACHER) {
            // teacher must teach the class
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
		$model=new ResHomework;
        $res_model = new ResResource;

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);

        $flag = false;
		if(isset($_POST['ResHomework']))
		{
            require('PurifierOptions.php');
            // filter html input
            $purifier = new CHtmlPurifier();
            $purifier->options = $p_options;
			$model->attributes=$_POST['ResHomework'];
            $model->teachingclass_id = $this->_teachingclass->id;
            $model->assignment_id = $this->_assignment->id;
            $model->student_id = $this->_student->id;
            $model->submit_time = date('y-m-d H:i:s',time()); 
            //$model->student_id = 45;
            $model->comments = $purifier->purify($model->comments);
            // save resource
            if(isset($_POST['ResResource']))
            {
                $res_model->attributes = $_POST['ResResource'];
                $flag = ResResourceController::saveModel($res_model, 2);
                $model->resource_id = $res_model->id;
            }
			if($flag && $model->save())
				$this->redirect(array('view','id'=>$model->id));
		}

		$this->render('create',array(
			'model'=>$model,
            'res_model'=>$res_model,
            'ass_model'=>$this->_assignment,
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
        $u_type = Yii::app()->user->type;
        if ($u_type == UserAuthentication::TYPE_STUDENT
            && $model->student_id != Yii::app()->user->id) {
            // student can only update its own homework
            throw new CHttpException(403,
                'You cannot edit others homework mokay?');
        } else if ($u_type == UserAuthentication::TYPE_TEACHER) {
            // teacher must teach the class
            $this->rightTeacher($model->teachingclass_id);
        }    

		// Uncomment the following line if AJAX validation is needed
		// $this->performAjaxValidation($model);
        $flag = false;
		if(isset($_POST['ResHomework']))
        {
            require('PurifierOptions.php');
			$model->attributes=$_POST['ResHomework'];
            $purifier = new CHtmlPurifier();
            $purifier->options = $p_options;
            $model->comments = $purifier->purify($model->comments);
            $model->submit_time = date('y-m-d H:i:s',time()); 
            $model->score = $model->score > 100 ? 100 : $model->score;
            // update related homework
            if (isset($_POST['ResResource'])) {
                $res_model->attributes = $_POST['ResResource'];
                $flag = ResResourceController::updateModel($res_model, $model->resource_id, 2);
            }
			if($model->save() && ($flag || Yii::app()->user->type==2))
				$this->redirect(array('view','id'=>$model->id));
		}

		$this->render('update',array(
			'model'=>$model,
            'res_model' => $res_model,
		));
	}

	/**
	 * Deletes a particular model.
	 * If deletion is successful, the browser will be redirected to the 'admin' page.
	 * @param integer $id the ID of the model to be deleted
	 */
	public function actionDelete($id)
	{
        $model = $this->loadModel($id);
        $u_type = Yii::app()->user->type;
        // filter users
        if ($u_type == UserAuthentication::TYPE_STUDENT
            && $model->student_id != Yii::app()->user->id) {
            throw new CHttpException(403,
                'You cannot edit others homework mokay?');
        } else if ($u_type == UserAuthentication::TYPE_TEACHER) {
            $this->rightTeacher($model->teachingclass_id);
        }    
		if(Yii::app()->request->isPostRequest)
		{
			// we only allow deletion via POST request
			$model->delete();
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
        // use params as filter
        if($u_type == UserAuthentication::TYPE_STUDENT) {
            // only display the homework of itself
            $this->rightStudent($this->_teachingclass->id);
            array_push($conds, 'student_id='.strval(Yii::app()->user->id));
        } else if ($u_type == UserAuthentication::TYPE_TEACHER) {
            $this->rightTeacher($this->_teachingclass->id);
        }
        if(isset($_GET['assignment_id'])) {
            array_push($conds, 
                'assignment_id='.strval((int)$_GET['assignment_id']));
        }
        if(isset($_GET['teachingclass_id'])) {
            array_push($conds,
                'teachingclass_id='.strval((int)$_GET['teachingclass_id']));
        }
        if(isset($_GET['student_id'])) {
            array_push($conds,
                'student_id'.strval((int)$_GET['student_id']));
        }
        // load the records
        $dataProvider = new CActiveDataProvider('ResHomework', array(
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
		$model=new ResHomework('search');
		$model->unsetAttributes();  // clear any default values
        // enter right context
		if(isset($_GET['ResHomework']))
            $model->attributes=$_GET['ResHomework'];
        if (isset($_GET['teachingclass_id'])) {
            $model->teachingclass_id=$_GET['teachingclass_id'];
        }
        if (isset($_GET['assignment_id'])) {
            $model->assignment_id = $_GET['assignment_id'];
        }

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
		$model=ResHomework::model()->findByPk($id);
		if($model===null)
			throw new CHttpException(404,'The requested page does not exist.');
		return $model;
	}

    /**
     * load the right teacher
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
     * Must in an assignment context
     */
    public function filterAssignmentContext($filterChain)
    {
        $assignmentId = null;
        if(isset($_GET['assignment_id'])){
            $assignmentId = $_GET['assignment_id'];
        } else if(isset($_POST['assignment_id'])){
            $assignmentId = $_POST['assignment_id'];
        }
        $this->loadAssignment($assignmentId);
        $this->loadTeachingclass($this->_assignment->teachingclass_id);
        $filterChain->run();
    }
    /**
     * Should be a student to view the page
     */ 
    public function filterBeStudent($filterChain)
    {
        if (Yii::app()->user->type != 1) {
            throw new CHttpException(403, 'You are not student!');
        }
        $studentId = Yii::app()->user->id;
        $this->loadStudent($studentId);

        $filterChain->run();
    }

    /**
     * The teacher must teach the class
     */ 
    public function filterRightTeacher($filterChain)
    {
        if (Yii::app()->user->type != 2) {
            throw new CHttpException(403, 'You are not the right teacher!');
        }
        if (!ClassTeacher::model()->exists(
                'classid=:cid and teacherid=:tid',
                array(':cid'=>$this->_teachingclass->id,
                ':tid'=>Yii::app()->user->id))) {
            throw new CHttpException(403,
               'You are not teaching this class'); 
        }
        $filterChain->run();
    }

    /**
     * must be teacher to view the page
     */ 
    public function filterBeTeacher($filterChain)
    {
        if (Yii::app()->user->type == 1) {
            throw new CHttpException(403, '=w=');
        }
        $filterChain->run();
    }

    /**
     * Should be the same student with the submitter
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
     * load the submitter
     */ 
    protected function loadStudent($studentId)
    {
        if($this->_student == null){
            $this->_student = StudentBasicInfo::model()->findbyPk($studentId);
            if($this->_student == null){
                throw new CHttpException(404,
                    'The request student does not exist.');
            }
        }
        return $this->_student;
    }

    /**
     * load the related assignment
     */ 
    protected function loadAssignment($assignment_id)
    {
        if($this->_assignment == null){
            $this->_assignment = ResAssignment::model()->findbyPk($assignment_id);
            if($this->_assignment == null){
                throw new CHttpException(404,
                    'The request assignment does not exist.');
            }
        }
        return $this->_assignment;
    }

    /**
     * load the related teachingclass 
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
	 * Performs the AJAX validation.
	 * @param CModel the model to be validated
	 */
	protected function performAjaxValidation($model)
	{
		if(isset($_POST['ajax']) && $_POST['ajax']==='res-homework-form')
		{
			echo CActiveForm::validate($model);
			Yii::app()->end();
		}
	}
}
