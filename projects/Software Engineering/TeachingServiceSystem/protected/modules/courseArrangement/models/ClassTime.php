<?php

/**
 * This is the model class for table "class_time".
 *
 * The followings are the available columns in table 'class_time':
 * @property string $id
 * @property string $class_id
 * @property string $classroom_id
 * @property integer $time
 * @property integer $isSingle
 */
class ClassTime extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return ClassTime the static model class
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
		return 'class_time';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('time, isSingle', 'required'),
			array('time, isSingle', 'numerical', 'integerOnly'=>true),
			array('id, class_id, classroom_id', 'length', 'max'=>11),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, class_id, classroom_id, time, isSingle', 'safe', 'on'=>'search'),
			
			//rules by jinrui
		//	array('time,classroom_id','courseTimeValid'),
			array('class','classidValid'),
			array('classroom_id','classroom_idValid'),
			array('time','teacherTimeValid','on'=>'update'),
		);
		
		
	}

	public function teacherTimeValid($attribute, $params){
		if(!$this->hasErrors()){
			
			
		}
	}
	
	
	/**
	 * if the courseID is valid
	 */
	public function courseTimeValid($attribute, $params){
		if(!$this->hasErrors()){
		
			$CT = ClassTeacher::model()->findAllBySql("select * from class_teacher where classid=".$this->class_id);
			$tid = $CT[0]->teacherid;
			
			$classtimes = ClassTime::model()->findAllBySql("select * from class_time where time=".$this->time." and id!=".$this->id,array());
			foreach($classtimes as $classtime)
			{
				$CT = ClassTeacher::model()->findAllBySql("select * from class_teacher where classid=".$classtime->class_id);
				$tid2 = $CT[0]->teacherid;
				if($tid2==$tid1)
				{
					$this->addError('time', Yii::t('courseArrangement','the teacher cannot have more than one class at same time'));
					break;
				}
			}
			
			
		}
	}
	
	public function classidValid($attribute, $params){
		if(!$this->hasErrors()){
			$classes = TeachingclassInfo::model()->findAllByPk($this->class_id);
			if(count($classes)==0){
				
				$this->addError('class_id', Yii::t('courseArrangement','this class not exists'));
			}
			
		}
	}
	
	public function classroom_idValid($attribute, $params){
		if(!$this->hasErrors()){
			if($this->classroom_id!=0)
			{
			$classrooms = ClassroomBasicInfo::model()->findAllByPk($this->classroom_id);
			if(count($classrooms)==0){
				
				$this->addError('classroom_id', Yii::t('courseArrangement','this classroom not exists'));
			}
			}
			
		}
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
			'id' => Yii::t('courseArrangement','List ClassTime'),
			'class_id' => Yii::t('courseArrangement','Class'),
			'classroom_id' => Yii::t('courseArrangement','Classroom'),
			'time' => Yii::t('courseArrangement','Time'),
			'isSingle' => Yii::t('courseArrangement','Is Single'),
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
		$criteria->compare('class_id',$this->class_id,true);
		$criteria->compare('classroom_id',$this->classroom_id,true);
		$criteria->compare('time',$this->time);
		$criteria->compare('isSingle',$this->isSingle);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}