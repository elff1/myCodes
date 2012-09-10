<?php

/**
 * This is the model class for table "course_waitlist".
 *
 * The followings are the available columns in table 'course_waitlist':
 * @property string $id
 * @property string $name
 * @property double $credit
 * @property integer $class
 * @property integer $prerequsite_required
 * @property string $introduction
 * @property string $syllabus
 * @property string $statement
 * @property string $department_id
 * @property integer $priority
 *
 * The followings are the available model relations:
 * @property Department $department
 */
class CourseWaitlist extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return CourseWaitlist the static model class
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
		return 'course_waitlist';
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
			array('name', 'length', 'max'=>32),
			array('introduction, syllabus, statement', 'length', 'max'=>2048),
			array('department_id', 'length', 'max'=>11),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, name, credit, class, prerequsite_required, introduction, syllabus, statement, department_id, priority, pass', 'safe', 'on'=>'search'),
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
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	//变量在显示时的映射名称，用于翻译
	public function attributeLabels()
	{
		return array(
			'id' => InformationManagementModule::t('courseWaitlist','ID'),
			'name' => InformationManagementModule::t('courseWaitlist','Name'),
			'credit' => InformationManagementModule::t('courseWaitlist','Credit'),
			'class' => InformationManagementModule::t('courseWaitlist','Class'),
			'prerequsite_required' => InformationManagementModule::t('courseWaitlist','Prerequsite Required'),
			'introduction' => InformationManagementModule::t('courseWaitlist','Introduction'),
			'syllabus' => InformationManagementModule::t('courseWaitlist','Syllabus'),
			'statement' => InformationManagementModule::t('courseWaitlist','Statement'),
			'department_id' => InformationManagementModule::t('courseWaitlist','Department'),
			'priority' => InformationManagementModule::t('courseWaitlist','Priority'),
			'pass' => InformationManagementModule::t('courseWaitlist','Status'),
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
		$criteria->compare('name',$this->name,true);
		$criteria->compare('credit',$this->credit);
		$criteria->compare('class',$this->class);
		$criteria->compare('prerequsite_required',$this->prerequsite_required);
		$criteria->compare('introduction',$this->introduction,true);
		$criteria->compare('syllabus',$this->syllabus,true);
		$criteria->compare('statement',$this->statement,true);
		$criteria->compare('department_id',$this->department_id,true);
		$criteria->compare('priority',$this->priority);
		$criteria->compare('pass',$this->pass);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}