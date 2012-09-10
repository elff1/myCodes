<?php

/**
 * This is the model class for table "personal_info".
 *
 * The followings are the available columns in table 'personal_info':
 * @property string $id
 * @property string $first_name
 * @property string $last_name
 * @property integer $sex
 * @property string $photo
 * @property string $date_of_birth
 * @property integer $ethnic_group
 * @property integer $political_status
 * @property string $birth_place_city
 * @property string $birth_place_province
 * @property string $original_residence_city
 * @property string $original_residence_province
 * @property string $home_address
 * @property string $home_postcode
 * @property string $home_phone
 * @property string $email
 * @property string $phone
 * @property string $identity_card_number
 *
 * The followings are the available model relations:
 * @property AdminBasicInfo[] $adminBasicInfos
 * @property StudentBasicInfo[] $studentBasicInfos
 * @property SystemAdminBasicInfo[] $systemAdminBasicInfos
 * @property TeacherBasicInfo[] $teacherBasicInfos
 */
class PersonalInfo extends CActiveRecord
{	
	public $tempImagePath = null;
	public $image;//save the uploaded file, in case uploading one by one
	
	public function batchSetAttributes($data){ //for batch only, as a helper for the creation of 4 classes of users; if there's photo,
	//the original temp path is saved is tempImagePath.
		$num = count($data);
		if($num != 17) { //# of attributes must match
			throw new Exception('File reading error');
		}
		$this->first_name = trim($data[0]);
		$this->last_name = trim($data[1]);
		$this->sex = trim($data[2]);
		
		$fileName = trim($data[3]);
		if(!empty($fileName)){
			$file = Yii::app()->file->set($this->tempImageDir.'/'.$fileName);		
			if($file->exists && $file->isfile){
				$extension=strtolower($file->extension);
				if(!in_array($extension, $this->imageExtensionList)){
					throw new Exception('File reading error');
				}
				
				if($file->size > Yii::app()->params['maxBatchCreateFileSize']){
					throw new Exception('File reading error');
				}
				
				$t = microtime(true);
				$micro = sprintf("%06d",($t - floor($t)) * 1000000);
				$this->photo = date('YmdHis').$micro.rand(100000,999999).'.'.$file->extension;
				
				$this->tempImagePath = $this->tempImageDir.'/'.$fileName;
			} else {
				throw new Exception('File reading error');
			}
		}
		
		$this->date_of_birth = trim($data[4]);
		$this->ethnic_group = trim($data[5]);
		$this->political_status = trim($data[6]);
		$this->birth_place_city = trim($data[7]);
		$this->birth_place_province = trim($data[8]);
		$this->original_residence_city = trim($data[9]);
		$this->original_residence_province = trim($data[10]);
		$this->home_address = trim($data[11]);
		$this->home_postcode = trim($data[12]);
		$this->home_phone = trim($data[13]);
		$this->email = trim($data[14]);
		$this->phone = trim($data[15]);
		$this->identity_card_number = trim($data[16]);
	} 
	
	public function getImageExtensionList(){
		return array('jpg','png');
	}
	
	public function updatePhoto($oldPhotoPath){
		if($this->image!==null){
			$this->image->saveAs($this->imageDir.'/'.$this->photo);
			if(!empty($oldPhotoPath)){
				unlink($this->imageDir.'/'.$oldPhotoPath); //delete old photo
			}
		}
	}


	//return the dir that saves images. this is for uploading
	public function getImageDir(){
		return Yii::getPathOfAlias('application.uploads.profileImages');
	}
	
	//return the url of dir that saves images. this is for displaying.
	public function getImageUrl(){
		return Yii::app()->baseUrl.'/protected/uploads/profileImages';
	}
	
	//dir that saves temp images, for batch create
	public function getTempImageDir() {
		return Yii::getPathOfAlias('application.uploads.profileImages.temp');
	}
	
	public function setPhotoPath(){ //for single upload
		$this->image=CUploadedFile::getInstance($this,'image');
		if($this->image!==null) {//reset image path
			$t = microtime(true);
			$micro = sprintf("%06d",($t - floor($t)) * 1000000);
			$this->photo = date('YmdHis').$micro.rand(100000,999999).'.'.$this->image->extensionName;
		}
	}
	
	//get full name (first & last)
	public function getFullName(){
		$first;
		$last;
		if(empty($this->first_name)){
			$first = '<?>';
		} else {
			$first = $this->first_name;
		}
		
		if(empty($this->last_name)){
			$last = '<?>';
		} else {
			$last = $this->last_name;
		}
		
		return $last.' '.$first;
	}
	
	//when there's no personalInfo attached
	public function getNullName(){
		return '<?> <?>';
	}
	
	
	protected function beforeSave() {
		 foreach($this as $key=>$value){
		 	if(empty($value)){
		 		$this->$key = null;
		 	}
		 }
		 return parent::beforeSave();
	}
	

	public function getProvinceList(){ //a list of provinces, here it doesn't decouples well from City. 
		$models = City::model()->findAllByAttributes(array('pid'=>0));
		return CHtml::listData($models, 'id', 'name');
	}
	
	
	
	public function getCityList($pid) //a list of cities, based on province
	{
		$models = City::model()->findAllByAttributes(array('pid'=>$pid));
		return CHtml::listData($models, 'id', 'name');
	}
		
	
	public function getGenderOptions(){ //cannot generate city list/province list easily.
		return array(0=>InformationManagementModule::t('personalInfo','Male'),
		1=>InformationManagementModule::t('personalInfo','Female'));
	}

	

	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return PersonalInfo the static model class
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
		return 'personal_info';
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
			array('sex, ethnic_group, political_status', 'numerical', 'integerOnly'=>true),
			array('first_name, last_name', 'length', 'max'=>8),
			array('home_phone, phone', 'length', 'max'=>32),
			array('birth_place_city, birth_place_province, original_residence_city, original_residence_province', 'length', 'max'=>16),
			array('home_address, email', 'length', 'max'=>64),
			array('home_postcode', 'length', 'max'=>6),
			array('identity_card_number', 'length', 'max'=>18),
			array('date_of_birth', 'safe'),
			array('date_of_birth', 'date', 'format'=>'yyyy-MM-dd'), //date validation
			array('image','file','allowEmpty'=>true,'types'=>$this->imageExtensionList, 'maxSize'=>Yii::app()->params['maxBatchCreateFileSize']),
			array('sex', 'in', 'range'=>array(0,1)),
			
			array('email', 'email'),
			array('identity_card_number', 'length', 'is'=>18),
			
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, first_name, last_name, sex, photo, date_of_birth, ethnic_group, political_status, birth_place_city, birth_place_province, original_residence_city, original_residence_province, home_address, home_postcode, home_phone, email, phone, identity_card_number', 'safe', 'on'=>'search'),
			array('birth_place_city','legalBirthPlaceCity'),
			array('original_residence_city','legalOriginalResidenceCity'),
			array('home_phone, phone', 'match', 'pattern'=>'/^([0-9]{3,4}-[0-9]{7,8}|[0-9]{13})$/'),//合法的区号
			array('first_name, last_name', 'match', 'pattern'=>'/^([\x{4e00}-\x{9fa5}]|[a-zA-Z])+$/'),//合法的名字(汉字或者英文)
			array('home_postcode', 'match', 'pattern'=>'/^[0-9]{6}$/'),//合法的邮编
			
		);
	}
	
	//判断出生地是否合法
	public function legalBirthPlaceCity($attribute, $params){
		if(!$this->hasErrors()){
			if(!empty($this->birth_place_province) && !empty($this->birth_place_city)){
				$city = City::model()->findByPk($this->birth_place_city);
				if($city->pid != $this->birth_place_province){
					$this->addError('birth_place_city', InformationManagementModule::t('personalInfo','Invalid province/city combination.'));
				}
			}
		}
	}
	
	//判断户籍地是否合法
	public function legalOriginalResidenceCity($attribute, $params){
		if(!$this->hasErrors()){
			if(!empty($this->original_residence_province) && !empty($this->original_residence_city)){
				$city = City::model()->findByPk($this->original_residence_city);
				if($city->pid != $this->original_residence_province){
					$this->addError('original_residence_city', InformationManagementModule::t('personalInfo','Invalid province/city combination.'));
				}
			}
		}
	}
	
	//政治面貌的可能值
	public function getPoliticalStatusList(){
		return array(
		1 => '中共党员',
		2 => '中共预备党员',
		3 =>'共青团员',
		4=>'民革党员',
		5=>'民盟盟员',
		6=>'民建会员',
		7=>'民进会员',
		8=>'农工党党员',
		9=>'致公党党员',
		10=>'九三学社社员',
		11=>'台盟盟员',
		12=>'无党派民主人士',
		13=>'群众',);
	}
	
	public function getEthnicGroupList(){
		$data = EthnicGroup::model()->findAll();
		return CHtml::listData($data,'id','name');
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
			'adminBasicInfos' => array(self::HAS_MANY, 'AdminBasicInfo', 'personal_info_id'),
			'studentBasicInfos' => array(self::HAS_MANY, 'StudentBasicInfo', 'personal_info_id'),
			'systemAdminBasicInfos' => array(self::HAS_MANY, 'SystemAdminBasicInfo', 'personal_info_id'),
			'teacherBasicInfos' => array(self::HAS_MANY, 'TeacherBasicInfo', 'personal_info_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	//变量在显示时的映射名称，用于翻译
	public function attributeLabels()
	{
		return array(
			'id' => InformationManagementModule::t('personalInfo','ID'),
			'first_name' => InformationManagementModule::t('personalInfo','First Name'),
			'last_name' => InformationManagementModule::t('personalInfo','Last Name'),
			'sex' => InformationManagementModule::t('personalInfo','Sex'),
			'photo' => InformationManagementModule::t('personalInfo','Photo'),
			'date_of_birth' => InformationManagementModule::t('personalInfo','Date Of Birth'),
			'ethnic_group' => InformationManagementModule::t('personalInfo','Ethnic Group'),
			'political_status' => InformationManagementModule::t('personalInfo','Political Status'),
			'birth_place_city' => InformationManagementModule::t('personalInfo','Birth Place City'),
			'birth_place_province' => InformationManagementModule::t('personalInfo','Birth Place Province'),
			'original_residence_city' => InformationManagementModule::t('personalInfo','Original Residence City'),
			'original_residence_province' => InformationManagementModule::t('personalInfo','Original Residence Province'),
			'home_address' => InformationManagementModule::t('personalInfo','Home Address'),
			'home_postcode' => InformationManagementModule::t('personalInfo','Home Postcode'),
			'home_phone' => InformationManagementModule::t('personalInfo','Home Phone'),
			'email' => InformationManagementModule::t('personalInfo','Email'),
			'phone' => InformationManagementModule::t('personalInfo','Phone'),
			'identity_card_number' => InformationManagementModule::t('personalInfo','Identity Card Number'),
			'image'=> InformationManagementModule::t('personalInfo','Image'), //just use photo, since image is actually private
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
		$criteria->compare('first_name',$this->first_name,true);
		$criteria->compare('last_name',$this->last_name,true);
		$criteria->compare('sex',$this->sex);
		$criteria->compare('photo',$this->photo,true);
		$criteria->compare('date_of_birth',$this->date_of_birth,true);
		$criteria->compare('ethnic_group',$this->ethnic_group);
		$criteria->compare('political_status',$this->political_status);
		$criteria->compare('birth_place_city',$this->birth_place_city,true);
		$criteria->compare('birth_place_province',$this->birth_place_province,true);
		$criteria->compare('original_residence_city',$this->original_residence_city,true);
		$criteria->compare('original_residence_province',$this->original_residence_province,true);
		$criteria->compare('home_address',$this->home_address,true);
		$criteria->compare('home_postcode',$this->home_postcode,true);
		$criteria->compare('home_phone',$this->home_phone,true);
		$criteria->compare('email',$this->email,true);
		$criteria->compare('phone',$this->phone,true);
		$criteria->compare('identity_card_number',$this->identity_card_number,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}