<?php

/**
 * SystemAdminIdentity represents the data needed to identity a system admin.
 * It contains the authentication method that checks if the provided
 * data can identity the system admin.
 */
 //系统管理员身份验证类
class SystemAdminIdentity extends CUserIdentity
{
	/**
	 * Authenticates a user.
	 * The example implementation makes sure if the username and password
	 * are both 'demo'.
	 * In practical applications, this should be changed to authenticate
	 * against some persistent user identity storage (e.g. database).
	 * @return boolean whether authentication succeeds.
	 */
	 
	//real id to distinguish different users
	//唯一id
	private $_id;
	//验证密码的函数
	public function authenticate()
	{
		$record=SystemAdminBasicInfo::model()->findByAttributes(array('system_admin_id'=>$this->username));
		
		if($record===null){//找不到记录
			$this->errorCode=self::ERROR_USERNAME_INVALID;
		} else if ($record->id0===null) { //in fact, this implies an internal error.//内部错误
			throw new CDbException('Inconsistent reference among tables.'); //throw a CDbException.
		} else if (!($record->id0->checkPassword($this->password))) {//密码错误
			$this->errorCode=self::ERROR_PASSWORD_INVALID;
		} else {
			$this->_id = $record->id;
			//session 变量
			$this->setState('type', UserAuthentication::TYPE_SYSTEM_ADMIN);
			$this->setState('fullName', $record->fullName);
			$this->setState('userName', $record->system_admin_id);
			$this->setState('personalInfoID', $record->personal_info_id);
			$this->errorCode = self::ERROR_NONE;
		}
		return !$this->errorCode;
	}
	
	//重定义 id & name 属性
	public function getId() //so that 'id' returns auto-increment id, not login name.
	{
		return $this->_id;
	}
	
	public function getName(){
		return $this->_id;
	}
	
}