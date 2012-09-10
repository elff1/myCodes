<?php

/**
 * This is the model class for table "paper_bank".
 *
 * The followings are the available columns in table 'paper_bank':
 * @property string $id
 * @property string $teacher_id
 * @property string $course_id
 * @property integer $is_publish
 * @property string $timelimit
 *
 * The followings are the available model relations:
 * @property Paper[] $papers
 * @property TeacherBasicInfo $teacher
 * @property CourseBasicInfo $course
 * @property StuTestStatus[] $stuTestStatuses
 */
class PaperBank extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return PaperBank the static model class
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
		return 'paper_bank';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('teacher_id, course_id, timelimit', 'required'),
			array('is_publish', 'numerical', 'integerOnly'=>true),
			array('teacher_id, course_id', 'length', 'max'=>10),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, teacher_id, course_id, is_publish, timelimit', 'safe', 'on'=>'search'),
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
			'papers' => array(self::HAS_MANY, 'Paper', 'paper_id'),
			'teacher' => array(self::BELONGS_TO, 'TeacherBasicInfo', 'teacher_id'),
			'course' => array(self::BELONGS_TO, 'CourseBasicInfo', 'course_id'),
			'stuTestStatuses' => array(self::HAS_MANY, 'StuTestStatus', 'paper_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		return array(
			'id' => 'ID',
			'teacher_id' => 'Teacher',
			'course_id' => 'Course',
			'is_publish' => 'Is Publish',
			'timelimit' => 'Timelimit',
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

		$criteria->compare('id',$this->id,true);
		$criteria->compare('teacher_id',$this->teacher_id,true);
		$criteria->compare('course_id',$this->course_id,true);
		$criteria->compare('is_publish',$this->is_publish);
		$criteria->compare('timelimit',$this->timelimit,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}

	/**
	 * Get the options of is_publish.
	 * @return Array of the is_publish options
	 */
	public function getPublishOptions() {
		return array(
			0=>"False",
			1=>"True",
			);
	}

	/**
	 * Get the is_publish status.
	 * @return The is_publish status
	 */
	public function getIsPublish()
	{
		$publishOptions=$this->publishOptions;
		return isset($publishOptions[$this->is_publish]) ? $publishOptions[$this->is_publish] : "unknown status ({$this->status_id})";
	}
}