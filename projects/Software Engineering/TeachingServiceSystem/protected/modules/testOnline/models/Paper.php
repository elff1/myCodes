<?php

/**
 * This is the model class for table "paper".
 *
 * The followings are the available columns in table 'paper':
 * @property string $id
 * @property string $paper_id
 * @property string $pro_id
 * @property integer $pro_score
 *
 * The followings are the available model relations:
 * @property PaperBank $paper
 * @property QuestionBank $pro
 * @property TestRecording[] $testRecordings
 */
class Paper extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return Paper the static model class
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
		return 'paper';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('paper_id, pro_id, pro_score', 'required'),
			array('pro_score', 'numerical', 'integerOnly'=>true),
			array('paper_id', 'length', 'max'=>10),
			array('pro_id', 'length', 'max'=>20),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, paper_id, pro_id, pro_score', 'safe', 'on'=>'search'),
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
			'paper' => array(self::BELONGS_TO, 'PaperBank', 'paper_id'),
			'pro' => array(self::BELONGS_TO, 'QuestionBank', 'pro_id'),
			'testRecording' => array(self::HAS_MANY, 'TestRecording', 'paper_pro_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		return array(
			'id' => 'ID',
			'paper_id' => 'Paper',
			'pro_id' => 'Pro',
			'pro_score' => 'Pro Score',
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
		$criteria->compare('paper_id',$this->paper_id,true);
		$criteria->compare('pro_id',$this->pro_id,true);
		$criteria->compare('pro_score',$this->pro_score);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}