<?php

/**
 * This is the model class for table "res_homework".
 *
 * The followings are the available columns in table 'res_homework':
 * @property string $id
 * @property string $student_id
 * @property integer $score
 * @property string $assignment_id
 * @property string $resource_id
 * @property string $comments
 * @property string $teachingclass_id
 * @property string $submit_time
 *
 * The followings are the available model relations:
 * @property StudentBasicInfo $student
 * @property ResAssignment $assignment
 * @property ResResource $resource
 * @property TeachingclassInfo $teachingclass
 */
class ResHomework extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return ResHomework the static model class
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
		return 'res_homework';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('student_id, assignment_id, resource_id, teachingclass_id, submit_time', 'required'),
			array('score', 'numerical', 'integerOnly'=>true),
			array('student_id', 'length', 'max'=>11),
			array('assignment_id, resource_id, teachingclass_id', 'length', 'max'=>10),
			array('comments', 'length', 'max'=>1024),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, student_id, score, assignment_id, resource_id, comments, teachingclass_id, submit_time', 'safe', 'on'=>'search'),
            array('student_id', 'UniqueAttributesValidator', 'with'=>'assignment_id'),
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
			'student' => array(self::BELONGS_TO, 'StudentBasicInfo', 'student_id'),
			'assignment' => array(self::BELONGS_TO, 'ResAssignment', 'assignment_id'),
			'resource' => array(self::BELONGS_TO, 'ResResource', 'resource_id'),
			'teachingclass' => array(self::BELONGS_TO, 'TeachingclassInfo', 'teachingclass_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		return array(
			'id' => 'ID',
			'student_id' => ResourceModule::t('resHomework', 'Student'),
			'score' => ResourceModule::t('resHomework', 'Score'),
			'assignment_id' => ResourceModule::t('resHomework', 'Assignment'),
			'resource_id' => ResourceModule::t('resHomework', 'Resource'),
			'comments' => ResourceModule::t('resHomework', 'Comments'),
			'teachingclass_id' => ResourceModule::t('resHomework', 'Teachingclass'),
			'submit_time' => ResourceModule::t('resHomework', 'Submit Time'),
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
		$criteria->compare('student_id',$this->student_id,true);
		$criteria->compare('score',$this->score);
		$criteria->compare('assignment_id',$this->assignment_id,true);
		$criteria->compare('resource_id',$this->resource_id,true);
		$criteria->compare('comments',$this->comments,true);
		$criteria->compare('teachingclass_id',$this->teachingclass_id,true);
		$criteria->compare('submit_time',$this->submit_time,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}
