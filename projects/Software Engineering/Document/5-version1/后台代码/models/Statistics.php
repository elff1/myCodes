<?php

/**
 * This is the model class for table "statistic".
 *
 * The followings are the available columns in table 'statistic':
 * @property string $id
 * @property integer $done
 * @property integer $a
 * @property integer $b
 * @property integer $c
 * @property integer $d
 * @property string $pro_id
 *
 * The followings are the available model relations:
 * @property QuestionBank $pro
 */
class statistics extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return statistics the static model class
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
		return 'statistic';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('pro_id', 'required'),
			array('done, a, b, c, d', 'numerical', 'integerOnly'=>true),
			array('pro_id', 'length', 'max'=>20),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, done, a, b, c, d, pro_id', 'safe', 'on'=>'search'),
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
			'pro' => array(self::BELONGS_TO, 'QuestionBank', 'pro_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		return array(
			'id' => 'ID',
			'done' => 'Done',
			'a' => 'A',
			'b' => 'B',
			'c' => 'C',
			'd' => 'D',
			'pro_id' => 'Pro',
		);
	}

	/**
	 * Retrieves a list of models based on the current search/filter conditions.
	 * @return CActiveDataProvider the data provider that can return the models based on the search/filter conditions.
	 */
	public function search1()
	{
		// Warning: Please modify the following code to remove attributes that
		// should not be searched.

		$criteria=new CDbCriteria;

		$criteria->compare('id',$this->id,true);
		$criteria->compare('done',$this->done);
		$criteria->compare('a',$this->a);
		$criteria->compare('b',$this->b);
		$criteria->compare('c',$this->c);
		$criteria->compare('d',$this->d);
		$criteria->compare('pro_id',$this->pro_id,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
	public function search()
	{
		// Warning: Please modify the following code to remove attributes that
		// should not be searched.

		$criteria=new CDbCriteria;

		$criteria->compare('id',$this->id,true);
		$criteria->compare('done',$this->done);
		$criteria->compare('a',$this->a);
		$criteria->compare('b',$this->b);
		$criteria->compare('c',$this->c);
		$criteria->compare('d',$this->d);
		$criteria->compare('pro_id',$this->pro_id,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}