<?php

/**
 * This is the model class for table "teachingclass_info".
 *
 * The followings are the available columns in table 'teachingclass_info':
 * @property integer $class_id
 * @property string $course_num
 * @property string $max
 * @property string $term
 * @property string $campus
 * @property integer $dependence
 *
 * The followings are the available model relations:
 * @property ClassTeacher[] $classTeachers
 * @property ClassTime[] $classTimes
 * @property CourseSelAppByelection[] $courseSelAppByelections
 * @property CourseSelAppNormal[] $courseSelAppNormals
 * @property CourseSelSched[] $courseSelScheds
 * @property Exam[] $exams
 * @property CourseBasicInfo $courseNum
 */
class TeachingclassInfo extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return TeachingclassInfo the static model class
	 */
	public static function model($className=__CLASS__)
	{
		return parent::model($className);
	}

	/**
	 * @return string the associated database table name
	 */
	public function tableName()
	{
		return 'teachingclass_info';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('class_id, course_num', 'required'),
			array('class_id, dependence', 'numerical', 'integerOnly'=>true),
			array('course_num', 'length', 'max'=>9),
			array('max, term, campus', 'length', 'max'=>45),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('class_id, course_num, max, term, campus, dependence', 'safe', 'on'=>'search'),
		);
	}

	/**
	 * @return array relational rules.
	 */
	public function relations()
	{
		// NOTE: you may need to adjust the relation name and the related
		// class name for the relations automatically generated below.
		return array(
			'classTeachers' => array(self::HAS_MANY, 'ClassTeacher', 'classid'),
			'classTimes' => array(self::HAS_MANY, 'ClassTime', 'class_id'),
			'courseSelAppByelections' => array(self::HAS_MANY, 'CourseSelAppByelection', 'CLASS_ID'),
			'courseSelAppNormals' => array(self::HAS_MANY, 'CourseSelAppNormal', 'CLASS_ID'),
			'courseSelScheds' => array(self::HAS_MANY, 'CourseSelSched', 'CLASS_ID'),
			'exams' => array(self::HAS_MANY, 'Exam', 'class_id'),
			'courseNum' => array(self::BELONGS_TO, 'CourseBasicInfo', 'course_num'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		return array(
			'class_id' => 'Class',
			'course_num' => 'Course Num',
			'max' => 'Max',
			'term' => 'Term',
			'campus' => 'Campus',
			'dependence' => 'Dependence',
		);
	}

	/**
	 * Retrieves a list of models based on the current search/filter conditions.
	 * @return CActiveDataProvider the data provider that can return the models based on the search/filter conditions.
	 */
	public function search()
	{
		// Warning: Please modify the following code to remove attributes that
		// should not be searched.

		$criteria=new CDbCriteria;

		$criteria->compare('class_id',$this->class_id);
		$criteria->compare('course_num',$this->course_num,true);
		$criteria->compare('max',$this->max,true);
		$criteria->compare('term',$this->term,true);
		$criteria->compare('campus',$this->campus,true);
		$criteria->compare('dependence',$this->dependence);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}