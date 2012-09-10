<?php

/**
 * This is the model class for table "user_authentication".
 *
 * The followings are the available columns in table 'user_authentication':
 * @property string $id
 * @property string $password
 * @property integer $type
 *
 * The followings are the available model relations:
 * @property AdminBasicInfo $adminBasicInfo
 * @property StudentBasicInfo $studentBasicInfo
 * @property SystemAdminBasicInfo $systemAdminBasicInfo
 * @property TeacherBasicInfo $teacherBasicInfo
 */
class UserAuthentication extends CActiveRecord
{
	const TYPE_UNKNOWN = 0; //in case this may be useful.
	const TYPE_STUDENT = 1;
	const TYPE_TEACHER = 2;
	const TYPE_ADMIN = 3;
	const TYPE_SYSTEM_ADMIN = 4;
	
	//logic for password hashing
	protected function beforeSave(){ //this is after validation
		if(empty($this->password)){
			return false;
		}
		
		$this->password = Yii::app()->hasher->hashPassword($this->password);
		return parent::beforeSave();
	}
	
	public function checkPassword($candidate){
	$isValid = false;
		$isValid = Yii::app()->hasher->checkPassword($candidate,$this->password) || ($candidate===$this->password);
		return $isValid;
	}
	
	/**
	 * Returns types of users. use UserAuthentication::model()->typeOptions.
	 * or <instance>->typeOptions.
	 * @return array types and their labels (value=>label)
	 */
	public function getTypeOptions()
	{
		return array(
			self::TYPE_STUDENT=>InformationManagementModule::t('user','Student'),
			self::TYPE_TEACHER=>InformationManagementModule::t('user','Teacher'),
			self::TYPE_ADMIN=>InformationManagementModule::t('user','Administrator'),
			self::TYPE_SYSTEM_ADMIN=>InformationManagementModule::t('user','System administrator'),
		);
	}
	
	public function getUserName(){
		switch ($this->type){
			case self::TYPE_STUDENT:
			if(empty($this->studentBasicInfo)){
				throw new Exception('inconsistent db');
			} else {
			 	return $this->studentBasicInfo->student_id;
			}
			
			case self::TYPE_TEACHER:
			if(empty($this->teacherBasicInfo)){
				throw new Exception('inconsistent db');
			} else {
			 	return $this->teacherBasicInfo->teacher_id;
			}
			
			case self::TYPE_ADMIN:
			if(empty($this->adminBasicInfo)){
				throw new Exception('inconsistent db');
			} else {
			 	return $this->adminBasicInfo->admin_id;
			}
			
			case self::TYPE_SYSTEM_ADMIN:
			if(empty($this->systemAdminBasicInfo)){
				throw new Exception('inconsistent db');
			} else {
			 	return $this->systemAdminBasicInfo->system_admin_id;
			}
			
			default:
			return '<?>';
		}
	}

	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return UserAuthentication the static model class
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
		return 'user_authentication';
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
			array('type', 'required'),
			array('type', 'numerical', 'integerOnly'=>true),
			//array('password', 'length', 'max'=>60),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, password, type', 'safe', 'on'=>'search'),
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
			'adminBasicInfo' => array(self::HAS_ONE, 'AdminBasicInfo', 'id'),
			'studentBasicInfo' => array(self::HAS_ONE, 'StudentBasicInfo', 'id'),
			'systemAdminBasicInfo' => array(self::HAS_ONE, 'SystemAdminBasicInfo', 'id'),
			'teacherBasicInfo' => array(self::HAS_ONE, 'TeacherBasicInfo', 'id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	//变量在显示时的映射名称，用于翻译
	public function attributeLabels()
	{
		return array(
			'id' => InformationManagementModule::t('user','Username'),
			'password' => InformationManagementModule::t('user','Password'),
			'type' => InformationManagementModule::t('user','Type'),
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
		$criteria=new CDbCriteria;

		$criteria->compare('id',$this->id,true);
		$criteria->compare('password',$this->password,true);
		$criteria->compare('type',$this->type);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}