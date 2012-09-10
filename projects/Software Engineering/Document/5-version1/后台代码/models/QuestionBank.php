<?php

/**
 * This is the model class for table "question_bank".
 *
 * The followings are the available columns in table 'question_bank':
 * @property string $id
 * @property string $teacher_id
 * @property string $course_id
 * @property string $question
 * @property string $selection_a
 * @property string $selection_b
 * @property string $selection_c
 * @property string $selection_d
 * @property integer $type
 * @property string $answer
 *
 * The followings are the available model relations:
 * @property Paper[] $papers
 * @property TeacherBasicInfo $teacher
 * @property CourseBasicInfo $course
 * @property Statistic[] $statistics
 */
class QuestionBank extends CActiveRecord
{
	public static $CHOICE_TYPE = 0;
	public static $JUDGE_TYPE = 1;
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return QuestionBank the static model class
	 */
	public static function model($className=__CLASS__)
	{
		return parent::model($className);
	}

	
	/* (non-PHPdoc)
	 * @see CActiveRecord::beforeSave()
	 */
	protected function beforeSave() {
	 // TODO Auto-generated method stub
	  	return parent::beforeSave();
	}
		

	/**
	 * @return string the associated database table name
	 */
	public function tableName()
	{
		return 'question_bank';
	}

	// set name of options for displaying.
	public function getTypeOptions(){
		return array(0=>'Selection',1=>'Judge');
	}
	// maping option name to displayed value
	public function getAnswerOptions($option){
		if($option===0)
			return array('A'=>'A','B'=>'B','C'=>'C','D'=>'D');
		else if($option===1)
			return array('T'=>'T','F'=>'F');
	}
	
	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('teacher_id, course_id, question, selection_a, selection_b, selection_c, selection_d, type, answer', 'required'),
			array('type', 'numerical', 'integerOnly'=>true),
			array('teacher_id, course_id', 'length', 'max'=>10),
			array('question', 'length', 'max'=>500),
			array('selection_a, selection_b, selection_c, selection_d', 'length', 'max'=>100),
			array('answer', 'length', 'max'=>1),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('question, selection_a, selection_b, selection_c, selection_d, type, answer', 'safe', 'on'=>'search'),
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
			'papers' => array(self::HAS_MANY, 'Paper', 'pro_id'),
			'teacher' => array(self::BELONGS_TO, 'TeacherBasicInfo', 'teacher_id'),
			'course' => array(self::BELONGS_TO, 'CourseBasicInfo', 'course_id'),
			'statistics' => array(self::HAS_MANY, 'Statistic', 'pro_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
//	mapping from database entry name to displayed labels	
		return array(
			'id' => 'ID',
			'teacher_id' => 'Teacher',
			'course_id' => 'Course',
			'question' => 'Question',
			'selection_a' => 'Selection A',
			'selection_b' => 'Selection B',
			'selection_c' => 'Selection C',
			'selection_d' => 'Selection D',
			'type' => 'Type',
			'answer' => 'Answer',
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

		// set criteria for searching
		//
		$criteria=new CDbCriteria;

		$criteria->compare('id',$this->id,true);
		$criteria->compare('teacher_id',$this->teacher_id,true);
		$criteria->compare('course_id',$this->course_id,true);
		$criteria->compare('question',$this->question,true);
		$criteria->compare('selection_a',$this->selection_a,true);
		$criteria->compare('selection_b',$this->selection_b,true);
		$criteria->compare('selection_c',$this->selection_c,true);
		$criteria->compare('selection_d',$this->selection_d,true);
		$criteria->compare('type',$this->type,true);
		$criteria->compare('answer',$this->answer,true);

		$dp =  new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
		$cldata = $dp->data;
		foreach ($cldata as $key=>$value) {
			$at = $cldata[$key]->attributes;
			$at['type'] = $at['type']?'Judge':'Selection';
			$cldata[$key]->attributes=$at;
//			echo $key.':'.$value->attributes['type'].'<br>';
		}
		$dp->setdata($cldata);
		return $dp;
	}
	public function batchSetAttributes($data) {
		//TODO
		// set the values according to data offered from batch upload.
		// get the ids
		$teacher_id = AccountComponent::getSelected_Teacher_id();
		$course_id = AccountComponent::getSelected_course_id();


		// set values
		$this->teacher_id = $teacher_id;
		$this->course_id = $course_id;		
		$this->question = $data[0];
		$this->type = $data[1];
		$this->selection_a = $data[2];
		$this->selection_b = $data[3];
		$this->selection_c = $data[4];
		$this->selection_d = $data[5];
		$this->answer = $data[6];
		if ($this->type == 1) {
			$this->selection_a = 'null';
			$this->selection_b = 'null';
			$this->selection_c = 'null';
			$this->selection_d = 'null';
		}

	}
}
