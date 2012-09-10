<?php

/**
 * This is the model class for table "teachingclass_info".
 *
 * The followings are the available columns in table 'teachingclass_info':
 * @property string $id
 * @property string $course_num
 * @property string $max
 * @property string $term
 * @property string $campus
 * @property integer $dependence
 */
class TeachingclassInfo extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return TeachingclassInfo the static model class
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
		return 'teachingclass_info';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('course_num', 'required'),
			array('dependence', 'numerical', 'integerOnly'=>true),
			array('course_num', 'length', 'max'=>9),
			array('max, campus', 'length', 'max'=>45),
			array('term', 'length', 'max'=>11),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, course_num, max, term, campus, dependence', 'safe', 'on'=>'search'),
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
			'course_num' => 'Course Num',
			'max' => 'Max',
			'term' => 'Term',
			'campus' => 'Campus',
			'dependence' => 'Dependence',
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
		$criteria->compare('course_num',$this->course_num,true);
		$criteria->compare('max',$this->max,true);
		$criteria->compare('term',$this->term,true);
		$criteria->compare('campus',$this->campus,true);
		$criteria->compare('dependence',$this->dependence);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}