<?php

/**
 * This is the model class for table "res_assignment".
 *
 * The followings are the available columns in table 'res_assignment':
 * @property string $id
 * @property string $teachingclass_id
 * @property string $resource_id
 * @property string $dead_line
 * @property integer $is_published
 * @property integer $teacher_id
 * @property string $requirement
 *
 * The followings are the available model relations:
 * @property TeachingclassInfo $teachingclass
 * @property ResHomework[] $resHomeworks
 */
class ResAssignment extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return ResAssignment the static model class
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
		return 'res_assignment';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('teachingclass_id, dead_line, teacher_id, requirement', 'required'),
			array('is_published, teacher_id', 'numerical', 'integerOnly'=>true),
			array('teachingclass_id, resource_id', 'length', 'max'=>11),
			array('requirement', 'length', 'max'=>2048),
            array('dead_line', 'checkDeadline'),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, teachingclass_id, resource_id, dead_line, is_published, teacher_id, requirement', 'safe', 'on'=>'search'),
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
			'teachingclass' => array(self::BELONGS_TO, 'TeachingclassInfo', 'teachingclass_id'),
			'resHomeworks' => array(self::HAS_MANY, 'ResHomework', 'assignment_id'),
            'resource' => array(self::BELONGS_TO, 'ResResource', 'resource_id'),
            'teacher' => array(self::BELONGS_TO, 'TeacherBasicInfo', 'teacher_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		return array(
			'id' => 'ID',
			'teachingclass_id' => ResourceModule::t('resAssignment', 'Teachingclass'),
			'resource_id' => ResourceModule::t('resAssignment', 'Resource'),
			'dead_line' => ResourceModule::t('resAssignment', 'Dead Line'),
			'is_published' => ResourceModule::t('resAssignment', 'Is Published'),
			'teacher_id' => ResourceModule::t('resAssignment', 'Teacher'),
			'requirement' => ResourceModule::t('resAssignment', 'Requirement'),
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
		$criteria->compare('teachingclass_id',$this->teachingclass_id,true);
		$criteria->compare('resource_id',$this->resource_id,true);
		$criteria->compare('dead_line',$this->dead_line,true);
		$criteria->compare('is_published',$this->is_published);
		$criteria->compare('teacher_id',$this->teacher_id);
		$criteria->compare('requirement',$this->requirement,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}

    /**
     * The dealine cannot be before today 
     */  
    public function checkDeadline($attr, $params)
    {
        if ($this->$attr < date('Y-m-d H:i:s',time()))
            $this->addError($attr, 'No deadline before now');
    }

}
