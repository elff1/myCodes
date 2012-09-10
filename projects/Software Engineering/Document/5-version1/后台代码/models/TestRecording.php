<?php

/**
 * This is the model class for table "test_recording".
 *
 * The followings are the available columns in table 'test_recording':
 * @property string $id
 * @property string $student_id
 * @property string $paper_pro_id
 * @property string $choose
 * @property integer $score
 *
 * The followings are the available model relations:
 * @property StudentBasicInfo $student
 * @property Paper $paperPro
 */
class TestRecording extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return TestRecording the static model class
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
		return 'test_recording';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('paper_pro_id, choose', 'required'),
			array('paper_pro_id', 'length', 'max'=>15),
			array('choose', 'length', 'max'=>1),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, student_id, paper_pro_id, choose, score', 'safe', 'on'=>'search'),
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
			'student' => array(self::BELONGS_TO, 'StudentBasicInfo', 'student_id'),
			'paperPro' => array(self::BELONGS_TO, 'Paper', 'paper_pro_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		return array(
			'id' => 'ID',
			'student_id' => 'Student',
			'paper_pro_id' => 'Paper Pro',
			'choose' => 'Choose',
			'score' => 'Score',
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
		$criteria->compare('student_id',$this->student_id,true);
		$criteria->compare('paper_pro_id',$this->paper_pro_id,true);
		$criteria->compare('choose',$this->choose,true);
		$criteria->compare('score',$this->score);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}