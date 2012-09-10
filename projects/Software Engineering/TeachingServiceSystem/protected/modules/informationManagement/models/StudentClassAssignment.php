<?php

/**
 * This is the model class for table "student_class_assignment".
 *
 * The followings are the available columns in table 'student_class_assignment':
 * @property string $id
 * @property string $student_id
 * @property string $class_id
 *
 * The followings are the available model relations:
 * @property ClassBasicInfo $class
 * @property StudentBasicInfo $student
 */
class StudentClassAssignment extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return StudentClassAssignment the static model class
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
		return 'student_class_assignment';
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
			array('student_id, class_id', 'required'),
			array('student_id', 'length', 'max'=>11),
			array('class_id', 'length', 'max'=>10),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, student_id, class_id', 'safe', 'on'=>'search'),
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
			'class' => array(self::BELONGS_TO, 'ClassBasicInfo', 'class_id'),
			'student' => array(self::BELONGS_TO, 'StudentBasicInfo', 'student_id'),
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
			'student_id' => 'Student',
			'class_id' => 'Class',
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
		$criteria->compare('student_id',$this->student_id,true);
		$criteria->compare('class_id',$this->class_id,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}