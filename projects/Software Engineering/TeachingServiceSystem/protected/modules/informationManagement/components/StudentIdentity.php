<?php

/**
 * StudentIdentity represents the data needed to identity a student.
 * It contains the authentication method that checks if the provided
 * data can identity the student.
 */
  //学生身份验证类
class StudentIdentity extends CUserIdentity
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
	//检查用户名，密码是否匹配
	public function authenticate()
	{
		$record=StudentBasicInfo::model()->findByAttributes(array('student_id'=>$this->username));
		
		if($record===null){//找不到用户名
			$this->errorCode=self::ERROR_USERNAME_INVALID;
		} else if ($record->id0===null) { //in fact, this implies an internal error.//内部错误
			throw new CDbException('Inconsistent reference among tables.'); //throw a CDbException.
		} else if (!($record->id0->checkPassword($this->password))) { //method is encapsulated in UserAuthentication.
			$this->errorCode=self::ERROR_PASSWORD_INVALID;
		} else {
			$this->_id = $record->id;
			//session 变量
			$this->setState('type', UserAuthentication::TYPE_STUDENT);
			$this->setState('fullName', $record->fullName);
			$this->setState('userName', $record->student_id);
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