<?php

/**
 * This is the model class for table "student_basic_info".
 *
 * The followings are the available columns in table 'student_basic_info':
 * @property string $id
 * @property string $student_id
 * @property string $current_grade
 * @property string $program_id
 * @property string $entry_date
 * @property string $class_id
 * @property string $remark
 * @property string $personal_info_id
 *
 * The followings are the available model relations:
 * @property Program $program
 * @property PersonalInfo $personalInfo
 * @property ClassBasicInfo $class
 * @property UserAuthentication $id0
 * @property StudentClassAssignment[] $studentClassAssignments
 * @property StudentProgramAssignment[] $studentProgramAssignments
 */
class StudentBasicInfo extends CActiveRecord
{	
	//取学生的全名
	public function getFullName(){
		if(!empty($this->personal_info_id)){
			return $this->personalInfo->fullName;
		} else {
			return PersonalInfo::model()->nullName;
		}
	}

	//批量创建时，拆分用户提交的数据
	public function batchSetAttributes($data){ 
		$num = count($data);
		if($num != 6) { //# of attributes must match
			throw new Exception('File reading error');
		}
		$this->student_id = trim($data[0]);
		$this->current_grade = trim($data[1]);
		$this->program_id = trim($data[2]);
		$this->entry_date = trim($data[3]);
		$this->class_id = trim($data[4]);
		$this->remark = trim($data[5]);
	} 

	
	protected function beforeSave() {
		 foreach($this as $key=>$value){
		 	if(empty($value)){
		 		$this->$key = null;
		 	}
		 }
		 return parent::beforeSave();
	}
	
	
	public static function model($className=__CLASS__)
	{
		return parent::model($className);
	}

	/**
	 * @return string the associated database table name
	 */
	//用于存放对应的数据表的名称
	public function tableName()
	{
		return 'student_basic_info';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	//对应于数据表中的constraints，对数据的一些格式限定
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('student_id', 'required'),
			array('program_id, class_id', 'length', 'max'=>11),
			array('student_id', 'length', 'max'=>10),
			array('current_grade', 'length', 'max'=>4),
			array('remark', 'length', 'max'=>256),
			array('entry_date', 'safe'),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, student_id, current_grade, program_id, entry_date, class_id, remark, personal_info_id', 'safe', 'on'=>'search'),
			//personal_info_id cannot be changed from outside.
		);
	}

	/**
	 * @return array relational rules.
	 */
	//本Model对应的数据表的外键信息
	public function relations()
	{
		// NOTE: you may need to adjust the relation name and the related
		// class name for the relations automatically generated below.
		return array(
			'courseSelScheds' => array(self::HAS_MANY, 'CourseSelSched', 'stu_id'),
			'resHomeworks' => array(self::HAS_MANY, 'ResHomework', 'student_id'),
			'studentAchievement' => array(self::HAS_ONE, 'StudentAchievement', 'id'),
			'program' => array(self::BELONGS_TO, 'Program', 'program_id'),
			'personalInfo' => array(self::BELONGS_TO, 'PersonalInfo', 'personal_info_id'),
			'class' => array(self::BELONGS_TO, 'ClassBasicInfo', 'class_id'),
			'id0' => array(self::BELONGS_TO, 'UserAuthentication', 'id'),
			'studentClassAssignments' => array(self::HAS_MANY, 'StudentClassAssignment', 'student_id'),
			'studentProgramAssignments' => array(self::HAS_MANY, 'StudentProgramAssignment', 'student_id'),
			'tempRequests' => array(self::HAS_MANY, 'TempRequest', 'student_id'),
			'tempScores' => array(self::HAS_MANY, 'TempScore', 'student_id'),
			'testRecordings' => array(self::HAS_MANY, 'TestRecording', 'student_id'),
		);
	}
	/**
	 * @return array customized attribute labels (name=>label)
	 */
	//变量在显示时的映射名称，用于翻译
	public function attributeLabels()
	{
		return array(
			'id' => InformationManagementModule::t('studentBasicInfo','ID'),
			'student_id' => InformationManagementModule::t('studentBasicInfo','StudentID'),
			'current_grade' => InformationManagementModule::t('studentBasicInfo','Current Grade'),
			'program_id' => InformationManagementModule::t('studentBasicInfo','Program'),
			'entry_date' => InformationManagementModule::t('studentBasicInfo','Entry Date'),
			'class_id' => InformationManagementModule::t('studentBasicInfo','Class'),
			'remark' => InformationManagementModule::t('studentBasicInfo','Remark'),
			'personal_info_id' => InformationManagementModule::t('studentBasicInfo','Personal Info ID'),
		);
	}

	/**
	 * Retrieves a list of models based on the current search/filter conditions.
	 * @return CActiveDataProvider the data provider that can return the models based on the search/filter conditions.
	 */
	//搜索时创建一个新的DataProvider
	//用于匹配用户的输入并筛选数据
	public function search()
	{
		// Warning: Please modify the following code to remove attributes that
		// should not be searched.

		$criteria=new CDbCriteria;

		$criteria->compare('id',$this->id,true);
		$criteria->compare('student_id',$this->student_id,true);
		$criteria->compare('current_grade',$this->current_grade,true);
		$criteria->compare('program_id',$this->program_id,true);
		$criteria->compare('entry_date',$this->entry_date,true);
		$criteria->compare('class_id',$this->class_id,true);
		$criteria->compare('remark',$this->remark,true);
		$criteria->compare('personal_info_id',$this->personal_info_id,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}