<?php

/**
 * This is the model class for table "temp_request".
 *
 * The followings are the available columns in table 'temp_request':
 * @property string $id
 * @property string $teacher_id
 * @property string $teachingclass_id
 * @property string $student_id
 * @property integer $score
 * @property string $reason
 * @property integer $result
 * @property integer $is_handle
 * @property integer $is_ack
 */
class TempRequest extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return TempRequest the static model class
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
		return 'temp_request';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('teacher_id, teachingclass_id, student_id', 'required'),
			array('score, result, is_handle, is_ack', 'numerical', 'integerOnly'=>true),
			array('teacher_id, teachingclass_id, student_id', 'length', 'max'=>11),
			array('reason', 'length', 'max'=>512),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, teacher_id, teachingclass_id, student_id, score, reason, result, is_handle, is_ack', 'safe', 'on'=>'search'),
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
			'teacher_id' => 'Teacher',
			'teachingclass_id' => 'Teachingclass',
			'student_id' => 'Student',
			'score' => 'Score',
			'reason' => 'Reason',
			'result' => 'Result',
			'is_handle' => 'Is Handle',
			'is_ack' => 'Is Ack',
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
		$criteria->compare('teachingclass_id',$this->teachingclass_id,true);
		$criteria->compare('student_id',$this->student_id,true);
		$criteria->compare('score',$this->score);
		$criteria->compare('reason',$this->reason,true);
		$criteria->compare('result',$this->result);
		$criteria->compare('is_handle',$this->is_handle);
		$criteria->compare('is_ack',$this->is_ack);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}