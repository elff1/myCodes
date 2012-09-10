<?php

/**
 * LoginForm class.
 * LoginForm is the data structure for keeping
 * user login form data. It is used by the 'login' action of 'SiteController'.
 */
class LoginForm extends CFormModel
{
	public $username;
	public $password;
	public $rememberMe=false;
	
	//variable identifying login type
	public $userType;

	private $_identity;

	//wrapper for type options.
	public function getTypeOptions()
	{	
		return UserAuthentication::model()->typeOptions;
	}

	/**
	 * Declares the validation rules.
	 * The rules state that username and password are required,
	 * and password needs to be authenticated.
	 */
	public function rules()
	{
		return array(
			// username and password are required
			array('username, password', 'required'),
			// rememberMe needs to be a boolean
			array('rememberMe', 'boolean'),
			//userType must be specified
			array('userType', 'required'),
			// password needs to be authenticated
			array('password', 'authenticate'),
		);
	}

	/**
	 * Declares attribute labels.
	 */
	public function attributeLabels()
	{
		return array(
			'rememberMe'=>InformationManagementModule::t('user','Remember me next time'),
			'userType'=>InformationManagementModule::t('user','User type'),
			'username'=>InformationManagementModule::t('user','Username'),
			'password'=>InformationManagementModule::t('user','Password'),
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
			switch($this->userType){//use different UserIdentity, based on userType
				case UserAuthentication::TYPE_STUDENT:
				$this->_identity=new StudentIdentity($this->username,$this->password);
				break;
				
				case UserAuthentication::TYPE_TEACHER:
				$this->_identity=new TeacherIdentity($this->username,$this->password);
				break;
				
				case UserAuthentication::TYPE_ADMIN:
				$this->_identity=new AdminIdentity($this->username,$this->password);
				break;
				
				case UserAuthentication::TYPE_SYSTEM_ADMIN:
				$this->_identity=new SystemAdminIdentity($this->username,$this->password);
				break;
			}
			if(!$this->_identity->authenticate())
				$this->addError('password',Yii::t('user','Incorrect username or password.'));
		}
	}

	/**
	 * Logs in the user using the given username and password in the model.
	 * @return boolean whether login is successful
	 */
	public function login()
	{
		if($this->_identity===null)
		{
			switch($this->userType){//use different UserIdentity, based on userType
				case UserAuthentication::TYPE_STUDENT:
				$this->_identity=new StudentIdentity($this->username,$this->password);
				break;
				
				case UserAuthentication::TYPE_TEACHER:
				$this->_identity=new TeacherIdentity($this->username,$this->password);
				break;
				
				case UserAuthentication::TYPE_ADMIN:
				$this->_identity=new AdminIdentity($this->username,$this->password);
				break;
				
				case UserAuthentication::TYPE_SYSTEM_ADMIN:
				$this->_identity=new SystemAdminIdentity($this->username,$this->password);
				break;
			}
			$this->_identity->authenticate();
		}
		if($this->_identity->errorCode===UserIdentity::ERROR_NONE)
		{
			$duration=$this->rememberMe ? 3600*24*30 : 0; // 30 days
			Yii::app()->user->login($this->_identity,$duration);
			return true;
		}
		else
			return false;
	}
}
