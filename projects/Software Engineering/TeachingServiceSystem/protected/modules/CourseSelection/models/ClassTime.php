<?php

/**
 * This is the model class for table "class_time".
 *
 * The followings are the available columns in table 'class_time':
 * @property integer $id
 * @property integer $class_id
 * @property string $classroom_id
 * @property integer $time
 * @property integer $isSingle
 *
 * The followings are the available model relations:
 * @property TeachingclassInfo $class
 * @property ClassroomBasicInfo $classroom
 */
class ClassTime extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return ClassTime the static model class
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
		return 'class_time';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('id, class_id, classroom_id, time, isSingle', 'required'),
			array('id, class_id, time, isSingle', 'numerical', 'integerOnly'=>true),
			array('classroom_id', 'length', 'max'=>11),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, class_id, classroom_id, time, isSingle', 'safe', 'on'=>'search'),
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
			'class' => array(self::BELONGS_TO, 'TeachingclassInfo', 'class_id'),
			'classroom' => array(self::BELONGS_TO, 'ClassroomBasicInfo', 'classroom_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		return array(
			'id' => 'ID',
			'class_id' => 'Class',
			'classroom_id' => 'Classroom',
			'time' => 'Time',
			'isSingle' => 'Is Single',
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

		$criteria->compare('id',$this->id);
		$criteria->compare('class_id',$this->class_id);
		$criteria->compare('classroom_id',$this->classroom_id,true);
		$criteria->compare('time',$this->time);
		$criteria->compare('isSingle',$this->isSingle);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}