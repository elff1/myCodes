<?php

class DefaultController extends Controller
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
	 * auto-generated,as access rules
	 */
	public function accessRules()
	{
		return array(
			array('allow', // allow authenticated user to perform 'create' and 'update' actions
				'actions'=>array('index','view','create','update'),
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
	 * @param integer $student_id 
	 * @uses by default
	 */
	public function actionUpdateSelectedStudent($student_id) {
		Yii::app()->session->add('selected_student_id',$student_id);	//write the student into session
		Yii::app()->session->add('selected_teacher_id',-1);				//clear the select_teacher_id
		Yii::app()->session->add('selected_user_type',UserAuthentication::TYPE_STUDENT);	//write the type into session
		$this->render('/_listCourses');			//list the courses on the page
	}
	
	/**
	 * @param integer $teacher_id
	 * @uses by default
	 */
	public function actionUpdateSelectedTeacher($teacher_id) {
		Yii::app()->session->add('selected_teacher_id',$teacher_id);	//write the teacher into session
		Yii::app()->session->add('selected_student_id',-1);				//clear the select_student_id
		Yii::app()->session->add('selected_user_type',UserAuthentication::TYPE_TEACHER);	//write the type into session
		$this->render('/_listCourses');			//list the courses on the page
	}
	
	/**
	 * @uses by default
	 */
	public function actionListAll() {
		$this->render('/_listAll');			//list all the courses on the page
	}
	
	/**
	 * @uses by default
	 */
	public function actionListTaken() {
		$this->render('/_listCourses');			//list the selected courses on the page
	}
	
	/**
	 * @param integer $course_id
	 * @uses by default
	 */
	public function actionUpdateSelectedCourse($course_id) {
		Yii::app()->session->add('selected_course_id',$course_id);		//write the course into session
		$this->redirect (array('paperBank/'));							//redirect to the index of the paperBank
	}
	
	/**
	 * @param integer $paper_id
	 * @uses by default
	 */
	public function actionUpdateSelectedPaper($paper_id) {
		Yii::app()->session->add('selected_paper_id',$paper_id);		//write the paper into session
		$this->redirect (array('paperBank/view','id'=>$paper_id));		//redirect to the paper
	}
	
	/**
	 *the main page
	 */
	public function actionIndex()
	{
		$this->render('/../views/layouts/main');
	}
	
	/**
	 * list Courses
	 */
	public function actionListCourses()
	{
		$this->render('/_listCourses');
	}
}