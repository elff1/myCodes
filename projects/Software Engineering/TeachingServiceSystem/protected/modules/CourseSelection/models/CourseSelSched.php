<?php

/**
 * This is the model class for table "course_sel_sched".
 *
 * The followings are the available columns in table 'course_sel_sched':
 * @property string $ID
 * @property string $STU_ID
 * @property integer $CLASS_ID
 * @property string $REQUIRED
 * @property string $REPEATED
 * @property string $ABANDONED
 * @property integer $SCORE
 * @property integer $YEAR
 *
 * The followings are the available model relations:
 * @property StudentBasicInfo $sTU
 * @property TeachingclassInfo $cLASS
 */
class CourseSelSched extends CActiveRecord
{
	const MAX_TIME = 13;
	public $time;
	public $course_name;
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return CourseSelSched the static model class
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
		return 'course_sel_sched';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('STU_ID, CLASS_ID, REQUIRED, REPEATED, ABANDONED, SCORE, YEAR', 'required'),
			array('CLASS_ID, SCORE, YEAR', 'numerical', 'integerOnly'=>true),
			array('STU_ID', 'length', 'max'=>11),
			array('REQUIRED, REPEATED, ABANDONED', 'length', 'max'=>1),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('time,course_name', 'safe', 'on'=>'search'),
	//		array('CLASS_ID','required','on'=>'search'),
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
			'sTU' => array(self::BELONGS_TO, 'StudentBasicInfo', 'STU_ID'),
			'cLASS' => array(self::BELONGS_TO, 'TeachingclassInfo', 'CLASS_ID'),
//			'classTimes' => array(self::MANY_MANY, 'ClassTime', 'class_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		return array(
			'ID' => 'ID',
			'STU_ID' => 'Stu',
			'CLASS_ID' => 'Class',
			'REQUIRED' => 'Required',
			'REPEATED' => 'Repeated',
			'ABANDONED' => 'Abandoned',
			'SCORE' => 'Score',
			'YEAR' => 'Year',
		);
	}

	/**
	 * Retrieves a list of models based on the current search/filter conditions.
	 * @return CActiveDataProvider the data provider that can return the models based on the search/filter conditions.
	 */
	
	public function search($id)
	{
		// Warning: Please modify the following code to remove attributes that
		// should not be searched.
 
		$criteria=new CDbCriteria;
	
	//	$criteria->compare('ID',$this->ID,true);
	//	$criteria->compare('STU_ID',$this->STU_ID,true);
		$criteria->compare('STU_ID',$id,true);
		$criteria->compare('CLASS_ID',$this->CLASS_ID);
		$criteria->with=array('cLASS'=>array( 'with'=>array('courseNum'=>array('select'=>'name',),'classTimes'=>array('select'=>'classTimes.time','together'=>true))));
	//	$criteria->compare('REQUIRED',$this->REQUIRED,true);
	//	$criteria->compare('REPEATED',$this->REPEATED,true);
	//	$criteria->compare('ABANDONED',$this->ABANDONED,true);
	//	$criteria->compare('SCORE',$this->SCORE);
	//	$criteria->compare('YEAR',$this->YEAR);
	//	$criteria->compare('name',$this->cLASS->courseNum);
	//	$this->getRelated('cLASS',true)->getRelated(courseNum,true);
	    $criteria->compare('courseNum.name',$this->course_name,true);
		$criteria->compare('classTimes.time',$this->time,true);
	//	$criteria->compare('cLASS.courseNum.name',$this->time,true);
	/*
		$criteria->alias="s";
		$criteria->together=true;
		$criteria->join='left join class_time c on s.class_id = c.class_id';
	//	$criteria->join='left join teachingclass_info on s.class_id = teachingclass_info.class_id';
		$criteria->select='s.CLASS_ID,STU_ID,c.time';
	//	$criterai->with=array('classTimes'=>array('select'=>'time'));
	//	$criteria->with=array('cLASS'=>array('with'=>'courseNum'));
		
		
		$sql='select * from course_sel_sched s left join class_time  as t on s.class_id = t.class_id';
		$rows=Yii::app()->db->createCommand($sql)->queryAll();
		print_r($rows);
	
		
//		$rows=Yii::app()->db->createCommand($sql)->queryAll();
*/
//		$criteria->with=array('cLASS');
//		$rows=$this->findAll($criteria);
//		print_r($rows);
//		var_dump($this->getRelated('cLASS',true));
/*		
		
		
	*/
	/*
		$sql='select STU_ID,t.CLASS_ID,time from course_sel_sched s left join class_time t on s.class_id = t.class_id where STU_ID='.$id;
		$count=Yii::app()->db->createCommand('select COUNT(*) from course_sel_sched s left join class_time t on s.class_id = t.class_id where STU_ID='.$id)->queryScalar();
		$rows=Yii::app()->db->createCommand($sql)->queryAll();
		var_dump($rows);
		
		$sqlData = new CSqlDataProvider($sql,array(
		'totalItemCount'=>$count,
		'pagination'=>array(
				'pageSize'=>4
				),
		'keyField'=>'time'
		));
		return $sqlData;
	*/	
	var_dump($criteria->toArray());	
		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
			'pagination'=>array(
				'pageSize'=>10
				),
			'sort'=>array(
				'attributes'=>array(
					'course_name'=>array(
						'asc'=>'cLASS.courseNum.name',
						'desc'=>'cLASS.courseNum.name DESC',
					),
					'*',
				),
			),
		));
	}
	public function timeToStr( $time )
	{
		switch( $time )
		{
		case 1: return 'session 1,2 on Monday';
		case 2: return 'session 3,4 on Monday';
		default: return 'undefined';
		}
	}
}