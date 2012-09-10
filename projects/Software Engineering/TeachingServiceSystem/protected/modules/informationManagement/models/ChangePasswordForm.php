<?php

/**
 * ChangePasswordForm class.
 * ChangePasswordForm is the data structure for keeping
 * user password changing form data. It is used by the 'changePassword' action of 'SiteController'.
 */
class ChangePasswordForm extends CFormModel
{
	public $password;
	public $password_new_repeat;
	public $password_new;
	

	private $_identity;


	/**
	 * Declares the validation rules.
	 * The rules state that username and password are required,
	 * and password needs to be authenticated.
	 */
	//对应于数据表中的constraints，对数据的一些格式限定
	public function rules()
	{
		return array(
			// all three passwords are required
			array('password, password_new_repeat, password_new', 'required'),
			// password needs to be authenticated
			array('password', 'authenticate'),
			array('password_new', 'compare'),
		);
	}

	/**
	 * Declares attribute labels.
	 */
	//变量在显示时的映射名称，用于翻译
	public function attributeLabels()
	{
		return array(
			'password_new'=>InformationManagementModule::t('user','New Password'),
			'password'=>InformationManagementModule::t('user','Password'),
			'password_new_repeat'=>InformationManagementModule::t('user','New Password Repeat'),
		);
	}

	/**
	 * Authenticates the password.
	 * This is the 'authenticate' validator as declared in rules().
	 */
	public function authenticate($attribute,$params)
	{	
		if(!$this->hasErrors())
		{
			switch(Yii::app()->user->type){//use different UserIdentity, based on userType
				case UserAuthentication::TYPE_STUDENT:
				$this->_identity=new StudentIdentity(Yii::app()->user->userName,$this->password);
				break;
				
				case UserAuthentication::TYPE_TEACHER:
				$this->_identity=new TeacherIdentity(Yii::app()->user->userName,$this->password);
				break;
				
				case UserAuthentication::TYPE_ADMIN:
				$this->_identity=new AdminIdentity(Yii::app()->user->userName,$this->password);
				break;
				
				case UserAuthentication::TYPE_SYSTEM_ADMIN:
				$this->_identity=new SystemAdminIdentity(Yii::app()->user->userName,$this->password);
				break;
			}
			if(!$this->_identity->authenticate())
				$this->addError('password',InformationManagementModule::t('user','Incorrect password.'));
		}
	}

	/**
	 * Logs in the user using the given username and password in the model.
	 * @return boolean whether login is successful
	 */
}
