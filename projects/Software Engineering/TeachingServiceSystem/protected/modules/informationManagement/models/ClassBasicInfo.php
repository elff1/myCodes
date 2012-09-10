<?php

/**
 * This is the model class for table "class_basic_info".
 *
 * The followings are the available columns in table 'class_basic_info':
 * @property string $id
 * @property string $name
 * @property string $grade
 * @property string $tutor_id
 *
 * The followings are the available model relations:
 * @property TeacherBasicInfo $tutor
 * @property StudentBasicInfo[] $studentBasicInfos
 * @property StudentClassAssignment[] $studentClassAssignments
 */
class ClassBasicInfo extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return ClassBasicInfo the static model class
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
		return 'class_basic_info';
	}
	
	public function getClassList(){
		$recordArray = $this->findAll();
		return CHtml::listData($recordArray,'id','name');
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
			array('name', 'length', 'max'=>16),
			array('grade', 'length', 'max'=>4),
			array('tutor_id', 'length', 'max'=>11),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, name, grade, tutor_id', 'safe', 'on'=>'search'),
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
			'tutor' => array(self::BELONGS_TO, 'TeacherBasicInfo', 'tutor_id'),
			'studentBasicInfos' => array(self::HAS_MANY, 'StudentBasicInfo', 'class_id'),
			'studentClassAssignments' => array(self::HAS_MANY, 'StudentClassAssignment', 'class_id'),
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
			'name' => InformationManagementModule::t('classBasicInfo','Class Name'),
			'grade' => InformationManagementModule::t('classBasicInfo','Grade'),
			'tutor_id' => InformationManagementModule::t('classBasicInfo','Tutor'),
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
		$criteria->compare('grade',$this->grade,true);
		$criteria->compare('tutor_id',$this->tutor_id,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}