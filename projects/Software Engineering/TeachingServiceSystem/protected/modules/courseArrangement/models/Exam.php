<?php

/**
 * This is the model class for table "exam".
 *
 * The followings are the available columns in table 'exam':
 * @property integer $id
 * @property string $class_id
 * @property string $classroom_id
 * @property string $teacher1_id
 * @property string $teacher2_id
 * @property string $exam_time
 */
class Exam extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return Exam the static model class
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
		return 'exam';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('id, class_id, classroom_id, teacher1_id, teacher2_id, exam_time', 'required'),
			array('id', 'numerical', 'integerOnly'=>true),
			array('class_id, classroom_id, teacher1_id, teacher2_id', 'length', 'max'=>11),
			array('exam_time', 'length', 'max'=>45),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, class_id, classroom_id, teacher1_id, teacher2_id, exam_time', 'safe', 'on'=>'search'),
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
			'teacher1_id' => 'Teacher1',
			'teacher2_id' => 'Teacher2',
			'exam_time' => 'Exam Time',
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
		$criteria->compare('class_id',$this->class_id,true);
		$criteria->compare('classroom_id',$this->classroom_id,true);
		$criteria->compare('teacher1_id',$this->teacher1_id,true);
		$criteria->compare('teacher2_id',$this->teacher2_id,true);
		$criteria->compare('exam_time',$this->exam_time,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}