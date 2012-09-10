<?php

/**
 * This is the model class for table "classroom_basic_info".
 *
 * The followings are the available columns in table 'classroom_basic_info':
 * @property string $id
 * @property string $room_number
 * @property string $location
 * @property integer $campus
 * @property integer $type
 * @property string $capacity
 * @property string $college
 */
class ClassroomBasicInfo extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return ClassroomBasicInfo the static model class
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
		return 'classroom_basic_info';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('room_number','required'),
			array('type','required'),
			array('location','required'),
			array('capacity','required'),
			array('type', 'numerical', 'integerOnly'=>true),
			array('room_number, capacity', 'length', 'max'=>11),
			array('location', 'length', 'max'=>16),
			array('college', 'length', 'max'=>45),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, room_number, location, campus, type, capacity, college', 'safe', 'on'=>'search'),
			
			//rules by jinrui
			array('room_number','room_numberValid','on'=>'insert'),
			array('capacity','capacityValid'),
		);
	}
	
	/**
	 * if the room_number is valid
	 */
	public function room_numberValid($attribute, $params){
		if(!$this->hasErrors()){
			
			$rooms = $this->findAllByAttributes(array('room_number'=>$this->room_number));

			if(count($rooms)>0){
				$this->addError('room_number', Yii::t('courseArrangement','room number exists!'));
			}
			
		}
	}
	
	/**
	 * if the capacity is valid
	 */
	public function capacityValid($attribute, $params){
	if($this->capacity<=0){
				$this->addError('capacity', Yii::t('courseArrangement','capacity is not valid!'));
			}
	}
	
	
	/**
	 * @return array relational rules.
	 */
	public function relations()
	{
		// NOTE: you may need to adjust the relation name and the related
		// class name for the relations automatically generated below.
		return array(
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		return array(
			'id' => 'ID',
			'room_number' => 'Room Number',
			'location' => 'Location',
			'campus' => 'Campus',
			'type' => 'Type',
			'capacity' => 'Capacity',
			'college' => 'College',
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
		$criteria->compare('room_number',$this->room_number,true);
		$criteria->compare('location',$this->location,true);
		$criteria->compare('campus',$this->campus);
		$criteria->compare('type',$this->type);
		$criteria->compare('capacity',$this->capacity,true);
		$criteria->compare('college',$this->college,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}