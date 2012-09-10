<?php

/**
 * This is the model class for table "course_basic_info".
 *
 * The followings are the available columns in table 'course_basic_info':
 * @property string $id
 * @property string $course_id
 * @property string $name
 * @property double $credit
 * @property integer $class
 * @property integer $prerequsite_required
 * @property string $introduction
 * @property string $syllabus
 * @property string $department_id
 * @property integer $priority
 *
 * The followings are the available model relations:
 * @property Department $department
 * @property Prerequisite[] $prerequisites
 * @property Prerequisite[] $prerequisites1
 * @property ProgramDetail[] $programDetails
 */
class CourseBasicInfo extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return CourseBasicInfo the static model class
	 */
	public static function model($className=__CLASS__)
	{
		return parent::model($className);
	}

	/**
	 * @return string the associated database table name
	 */
	//用于存放对应的数据表的名称
	public function tableName()
	{
		return 'course_basic_info';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	//对应于数据表中的constraints，对数据的一些格式限定
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('class, prerequsite_required, priority', 'numerical', 'integerOnly'=>true),
			array('credit', 'numerical'),
			array('course_id', 'length', 'max'=>8),
			array('name', 'length', 'max'=>32),
			array('introduction, syllabus', 'length', 'max'=>2048),
			array('department_id', 'length', 'max'=>11),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, course_id, name, credit, class, prerequsite_required, introduction, syllabus, department_id, priority', 'safe', 'on'=>'search'),
		);
	}

	/**
	 * @return array relational rules.
	 */
	//本Model对应的数据表的外键信息
	public function relations()
	{
		// NOTE: you may need to adjust the relation name and the related
		// class name for the relations automatically generated below.
		return array(
			'department' => array(self::BELONGS_TO, 'Department', 'department_id'),
			'prerequisites' => array(self::HAS_MANY, 'Prerequisite', 'course_id'),
			'prerequisites1' => array(self::HAS_MANY, 'Prerequisite', 'prerequsite_course_id'),
			'programDetails' => array(self::HAS_MANY, 'ProgramDetail', 'course_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	//变量在显示时的映射名称，用于翻译
	public function attributeLabels()
	{
		return array(
			'id' => 'ID',
			'course_id' => InformationManagementModule::t('course','Course'),
			'name' => InformationManagementModule::t('course','Course Name'),
			'credit' => InformationManagementModule::t('course','Course Credit'),
			'class' => InformationManagementModule::t('course','Course Class'),
			'prerequsite_required' => InformationManagementModule::t('course','Prerequsite Required'),
			'introduction' => InformationManagementModule::t('course','Introduction'),
			'syllabus' => InformationManagementModule::t('course','Syllabus'),
			'department_id' => InformationManagementModule::t('course','Department'),
			'priority' => InformationManagementModule::t('course','Priority'),
		);
	}

	/**
	 * Retrieves a list of models based on the current search/filter conditions.
	 * @return CActiveDataProvider the data provider that can return the models based on the search/filter conditions.
	 */
	//搜索时创建一个新的DataProvider
	//用于匹配用户的输入并筛选数据
	public function search()
	{
		// Warning: Please modify the following code to remove attributes that
		// should not be searched.

		$criteria=new CDbCriteria;
		
		$criteria->compare('id',$this->id,true);
		$criteria->compare('course_id',$this->course_id,true);
		$criteria->compare('name',$this->name,true);
		$criteria->compare('credit',$this->credit);
		$criteria->compare('class',$this->class);
		$criteria->compare('prerequsite_required',$this->prerequsite_required);
		$criteria->compare('introduction',$this->introduction,true);
		$criteria->compare('syllabus',$this->syllabus,true);
		$criteria->compare('department_id',$this->department_id,true);
		$criteria->compare('priority',$this->priority);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}