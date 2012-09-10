<?php

class AccountComponent extends CApplicationComponent {

	/**
	 * @param 
	 * @return CActiveDataProvider:courses of the loggined person
	 * @uses by all
	 */
	public static function getCourses()
	{
		$userId=AccountComponent::getUserID();		//get the user logging in
		$userType=AccountComponent::getUserType();	//get the type of the current user
		/**********************find the classes that the current user take begins*******************************/
		switch($userType){
			case UserAuthentication::TYPE_TEACHER:	//teacher
				$models = ClassTeacher::model()->findAllByAttributes(array('teacherid'=>$userId));
				$classes = CHtml::listData($models,'id','classid');
				break;
			case UserAuthentication::TYPE_STUDENT:	//student
				$models = CourseSelSched::model()->findAllByAttributes(array('stu_id'=>$userId));
				$classes = CHtml::listData($models,'id','class_id');
				break;
			case UserAuthentication::TYPE_ADMIN:	//administors
			case UserAuthentication::TYPE_SYSTEM_ADMIN:
				$select_teacher_id=AccountComponent::getSelected_Teacher_id();
				if($select_teacher_id!==-1){		//play as a teacher
					$models = ClassTeacher::model()->findAllByAttributes(array('teacherid'=>AccountComponent::getSelected_Teacher_id()));
					$classes = CHtml::listData($models,'id','classid');
				}
				else{								//play as a student
					$models = CourseSelSched::model()->findAllByAttributes(array('stu_id'=>AccountComponent::getSelected_Student_id()));
					$classes = CHtml::listData($models,'id','class_id');
				}
				break;
		}
		/**********************find the classes that the current user take ends*******************************/
		/*********************find the distinct course_ids of the classes begins******************************/
		$criteria1 = new CDbCriteria;
		$criteria1->addInCondition('id', $classes);
		$criteria1->distinct = TRUE;
		$models = TeachingClassInfo::model()->findAll($criteria1);
		$courses = CHtml::listData($models,'id','course_num');
		/*********************find the distinct course_ids of the classes ends******************************/
		$criteria2 = new CDbCriteria;
		$criteria2->addInCondition('id',$courses);
		/*********************return the information of the courses begins******************************/
		return new CActiveDataProvider(CourseBasicInfo::model(), array(
			'criteria'=>$criteria2,
		));
	}
	
	/**
	 * @param
	 * @return CActiveDataProvider of all the students
	 * @uses by _listStudents
	 */
	public static function getStudentList()
	{
		return new CActiveDataProvider(StudentBasicInfo::model());
	}
	
	/**
	 * @param
	 * @return CActiveDataProvider of all teachers
	 * @uses by _listTeachers
	 */
	public static function getTeacherList(){
		return new CActiveDataProvider(TeacherBasicInfo::model());
	}
	
	/**
	 * @param
	 * @return TYPE of the current user
	 * @uses by all
	 */
	public static function getUserType(){
		if(Yii::app()->user->isGuest){
			return UserAuthentication::TYPE_UNKNOWN;
		}
		else
			return Yii::app()->user->type;
	}
	
	/**
	 * @param
	 * @return TYPE of the role that the administor select
	 * @uses by all
	 */
	public static function getUserSelectedType(){
		return Yii::app()->session->get('selected_user_type');
	}
	
	/**
	 * @param
	 * @return ID of the current user
	 * @uses by all
	 */
	public static function getUserID(){
		return Yii::app()->user->id;
	}
	
	/**
	 * @param
	 * @return fullname of the current user
	 * @uses by all
	 */
	public static function getUserName(){
		return Yii::app()->user->fullName;
	}
	
	/**
	 * @return the $selected_course_id
	 */
	public static function getSelected_course_id() {
		return Yii::app()->session->get('selected_course_id');
	}
	
	/**
	 * @return the $selected_course_name
	 */
	public static function getSelected_course_name() {
		$course_model = CourseBasicInfo::model()->findAllByAttributes(array('id'=>Yii::app()->session->get('selected_course_id')));
		$course_name = CHtml::listData ( $course_model, 'id','name');
		return end($course_name);
	}
	
	/**
	 * @return the $selected_paper_id
	 */
	public static function getSelected_paper_id() {
		return Yii::app()->session->get('selected_paper_id');
	}
	
	/**
	 * @return the $selected_teacher_id
	 */
	public static function getSelected_Teacher_id() {
		//if the user is teacher, return his ID, else return the teacher_id that the adminitor selects
		if(AccountComponent::getUserType()===UserAuthentication::TYPE_TEACHER)
			return AccountComponent::getUserID();
		return Yii::app()->session->get('selected_teacher_id');
	}
	
	/**
	 * @return the $selected_student_id
	 */
	public static function getSelected_Student_id() {
		//if the user is student, return his ID, else return the student_id that the adminitor selects
		if(AccountComponent::getUserType()===UserAuthentication::TYPE_STUDENT)
			return AccountComponent::getUserID();
		return Yii::app()->session->get('selected_student_id');
	}
	
	/**
	 * @return the teacher_id of the select_course_id that the student selects
	 */
	public static function getStudentTeacherID(){
		//find the model of the course_schedule that the student selects
		$models=CourseSelSched::model()->findAllByAttributes(array('stu_id'=>AccountComponent::getSelected_Student_id()));
		$classes = CHtml::listData($models,'id','class_id');
		//find the teaching_classes that the students selects
		$criteria1 = new CDbCriteria;
		$criteria1->addInCondition('id', $classes);
		$criteria1->compare('course_num',AccountComponent::getSelected_course_id());
		$class=TeachingclassInfo::model()->findAll($criteria1);
		$class_id=CHtml::listData($class,'id','id');
		//find the teachers of the classes
		$teacher=CHtml::listData(ClassTeacher::model()->findAllByAttributes(array('classid'=>end($class_id))),'id','teacherid');
		return end($teacher);//return a teacher,$teacher is array(1)
	}
}

?>