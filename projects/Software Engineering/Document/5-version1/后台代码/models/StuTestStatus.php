<?php

/**
 * This is the model class for table "stu_test_status".
 *
 * The followings are the available columns in table 'stu_test_status':
 * @property string $id
 * @property string $stu_id
 * @property string $paper_id
 * @property string $start_time
 * @property string $end_time
 * @property integer $is_submit
 * @property string $last_pro_pos
 *
 * The followings are the available model relations:
 * @property StudentBasicInfo $stu
 * @property PaperBank $paper
 */
class StuTestStatus extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return StuTestStatus the static model class
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
		return 'stu_test_status';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('stu_id, paper_id, start_time', 'required'),
			array('is_submit', 'numerical', 'integerOnly'=>true),
			array('stu_id, paper_id, last_pro_pos', 'length', 'max'=>10),
			array('end_time', 'safe'),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, stu_id, paper_id, start_time, end_time, is_submit, last_pro_pos', 'safe', 'on'=>'search'),
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
			'stu' => array(self::BELONGS_TO, 'StudentBasicInfo', 'stu_id'),
			'paper' => array(self::BELONGS_TO, 'PaperBank', 'paper_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		return array(
			'id' => 'ID',
			'stu_id' => 'Stu',
			'paper_id' => 'Paper',
			'start_time' => 'Start Time',
			'end_time' => 'End Time',
			'is_submit' => 'Is Submit',
			'last_pro_pos' => 'Last Pro Pos',
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
		$criteria->compare('stu_id',$this->stu_id,true);
		$criteria->compare('paper_id',$this->paper_id,true);
		$criteria->compare('start_time',$this->start_time,true);
		$criteria->compare('end_time',$this->end_time,true);
		$criteria->compare('is_submit',$this->is_submit);
		$criteria->compare('last_pro_pos',$this->last_pro_pos,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}