<?php

/**
 * This is the model class for table "teacher_basic_info".
 *
 * The followings are the available columns in table 'teacher_basic_info':
 * @property string $id
 * @property string $teacher_id
 * @property integer $title
 * @property string $department_id
 * @property string $personal_info_id
 *
 * The followings are the available model relations:
 * @property ClassBasicInfo[] $classBasicInfos
 * @property Department $department
 * @property UserAuthentication $id0
 * @property PersonalInfo $personalInfo
 */
class TeacherBasicInfo extends CActiveRecord
{
	//获取用户全名

	public function getTitleOptions(){ //ad hoc, the titles are fixed
		return array( 0=>'助教', 1=>'讲师', 2=>'副教授', 3=>'教授');
	}

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
		if($num != 3) { //# of attributes must match
			throw new Exception('File reading error');
		}
		$this->teacher_id = trim($data[0]);
		$this->title = trim($data[1]);
		$this->department_id = trim($data[2]);
	} 

	
	protected function beforeSave() {
		 foreach($this as $key=>$value){
		 	if(empty($value)){
		 		$this->$key = null;
		 	}
		 }
		 return parent::beforeSave();
	}
	
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return TeacherBasicInfo the static model class
	 */
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
		return 'teacher_basic_info';
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
			array('teacher_id', 'required'),
			array('title', 'numerical', 'integerOnly'=>true),
			array('department_id, personal_info_id', 'length', 'max'=>11),
			array('teacher_id', 'length', 'max'=>10),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, teacher_id, title, department_id, personal_info_id', 'safe', 'on'=>'search'),
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
			'classBasicInfos' => array(self::HAS_MANY, 'ClassBasicInfo', 'tutor_id'),
			'department' => array(self::BELONGS_TO, 'Department', 'department_id'),
			'id0' => array(self::BELONGS_TO, 'UserAuthentication', 'id'),
			'personalInfo' => array(self::BELONGS_TO, 'PersonalInfo', 'personal_info_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	//变量在显示时的映射名称，用于翻译

	public function attributeLabels()
	{
		return array(
			'id' => InformationManagementModule::t('teacherBasicInfo','ID'),
			'teacher_id' => InformationManagementModule::t('teacherBasicInfo','Teacher'),
			'title' => InformationManagementModule::t('teacherBasicInfo','Title'),
			'department_id' => InformationManagementModule::t('teacherBasicInfo','Department'),
			'personal_info_id' => InformationManagementModule::t('teacherBasicInfo','Personal Info ID'),
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
		$criteria->compare('teacher_id',$this->teacher_id,true);
		$criteria->compare('title',$this->title);
		$criteria->compare('department_id',$this->department_id,true);
		$criteria->compare('personal_info_id',$this->personal_info_id,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}