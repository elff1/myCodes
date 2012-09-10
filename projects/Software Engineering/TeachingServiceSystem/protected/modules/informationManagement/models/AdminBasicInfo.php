<?php

/**
 * This is the model class for table "admin_basic_info".
 *
 * The followings are the available columns in table 'admin_basic_info':
 * @property string $id
 * @property string $admin_id
 * @property string $personal_info_id
 *
 * The followings are the available model relations:
 * @property PersonalInfo $personalInfo
 * @property UserAuthentication $id0
 */
class AdminBasicInfo extends CActiveRecord
{
	//获取用户全名
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
		if($num != 1) { //# of attributes must match
			throw new Exception('File reading error');
		}
		$this->admin_id = trim($data[0]);
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
	 * @return AdminBasicInfo the static model class
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
		return 'admin_basic_info';
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
			array('admin_id', 'required'),
			array('personal_info_id', 'length', 'max'=>11),
			array('admin_id', 'length', 'max'=>10),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, admin_id, personal_info_id', 'safe', 'on'=>'search'),
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
			'personalInfo' => array(self::BELONGS_TO, 'PersonalInfo', 'personal_info_id'),
			'id0' => array(self::BELONGS_TO, 'UserAuthentication', 'id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	//变量在显示时的映射名称，用于翻译
	public function attributeLabels()
	{
		return array(
			'id' => InformationManagementModule::t('adminBasicInfo','ID'),
			'admin_id' => InformationManagementModule::t('adminBasicInfo','Admin'),
			'personal_info_id' => InformationManagementModule::t('adminBasicInfo','Personal Info ID'),
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
		$criteria->compare('admin_id',$this->admin_id,true);
		$criteria->compare('personal_info_id',$this->personal_info_id,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}