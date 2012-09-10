<?php

/**
 * This is the model class for table "student_achievement".
 *
 * The followings are the available columns in table 'student_achievement':
 * @property string $id
 * @property integer $gpa_major
 * @property integer $gpa_total
 * @property integer $credit_total
 * @property integer $credit_achieve
 * @property integer $credit_major_total
 * @property integer $credit_major_achieve
 */
class StudentAchievement extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return StudentAchievement the static model class
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
		return 'student_achievement';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('id', 'required'),
			array('gpa_major, gpa_total, credit_total, credit_achieve, credit_major_total, credit_major_achieve', 'numerical', 'integerOnly'=>true),
			array('id', 'length', 'max'=>11),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, gpa_major, gpa_total, credit_total, credit_achieve, credit_major_total, credit_major_achieve', 'safe', 'on'=>'search'),
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
			'gpa_major' => 'Gpa Major',
			'gpa_total' => 'Gpa Total',
			'credit_total' => 'Credit Total',
			'credit_achieve' => 'Credit Achieve',
			'credit_major_total' => 'Credit Major Total',
			'credit_major_achieve' => 'Credit Major Achieve',
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
		$criteria->compare('gpa_major',$this->gpa_major);
		$criteria->compare('gpa_total',$this->gpa_total);
		$criteria->compare('credit_total',$this->credit_total);
		$criteria->compare('credit_achieve',$this->credit_achieve);
		$criteria->compare('credit_major_total',$this->credit_major_total);
		$criteria->compare('credit_major_achieve',$this->credit_major_achieve);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}