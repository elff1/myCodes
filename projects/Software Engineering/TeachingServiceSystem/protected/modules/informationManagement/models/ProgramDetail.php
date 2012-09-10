<?php

/**
 * This is the model class for table "program_detail".
 *
 * The followings are the available columns in table 'program_detail':
 * @property string $id
 * @property string $program_id
 * @property string $course_id
 * @property integer $type
 * @property integer $required
 * @property integer $recommended_year
 * @property integer $recommended_term
 *
 * The followings are the available model relations:
 * @property Program $program
 * @property CourseBasicInfo $course
 */
class ProgramDetail extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return ProgramDetail the static model class
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
		return 'program_detail';
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
			array('course_id', 'required'),
			array('type, required, recommended_year, recommended_term', 'numerical', 'integerOnly'=>true),
			array('course_id', 'length', 'max'=>11),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, program_id, course_id, type, required, recommended_year, recommended_term', 'safe', 'on'=>'search'),
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
			'program' => array(self::BELONGS_TO, 'Program', 'program_id'),
			'course' => array(self::BELONGS_TO, 'CourseBasicInfo', 'course_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	//变量在显示时的映射名称，用于翻译
	public function attributeLabels()
	{
		return array(
			'id' => InformationManagementModule::t('programDetail','ID'),
			'program_id' => InformationManagementModule::t('programDetail','Program'),
			'course_id' => InformationManagementModule::t('programDetail','Course'),
			'type' => InformationManagementModule::t('programDetail','Type'),
			'required' => InformationManagementModule::t('programDetail','Required'),
			'recommended_year' => InformationManagementModule::t('programDetail','Recommended Year'),
			'recommended_term' => InformationManagementModule::t('programDetail','Recommended Term'),
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
		$criteria->compare('program_id',$this->program_id,true);
		$criteria->compare('course_id',$this->course_id,true);
		$criteria->compare('type',$this->type);
		$criteria->compare('required',$this->required);
		$criteria->compare('recommended_year',$this->recommended_year);
		$criteria->compare('recommended_term',$this->recommended_term);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}