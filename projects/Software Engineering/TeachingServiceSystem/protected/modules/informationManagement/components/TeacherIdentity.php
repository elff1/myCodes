<?php

/**
 * TeacherIdentity represents the data needed to identity a teacher.
 * It contains the authentication method that checks if the provided
 * data can identity the teacher.
 */
 //教师身份验证类
class TeacherIdentity extends CUserIdentity
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
	//验证函数
	public function authenticate()
	{
		$record=TeacherBasicInfo::model()->findByAttributes(array('teacher_id'=>$this->username));
		
		if($record===null){//用户名不存在
			$this->errorCode=self::ERROR_USERNAME_INVALID;
		} else if ($record->id0===null) { //in fact, this implies an internal error.
			throw new CDbException('Inconsistent reference among tables.'); //throw a CDbException.
		} else if (!($record->id0->checkPassword($this->password))) {
			$this->errorCode=self::ERROR_PASSWORD_INVALID;//密码错误
		} else {
			$this->_id = $record->id;
			//session 变量
			$this->setState('type', UserAuthentication::TYPE_TEACHER);
			$this->setState('fullName', $record->fullName);
			$this->setState('userName', $record->teacher_id);
			$this->setState('personalInfoID', $record->personal_info_id);
			$this->errorCode = self::ERROR_NONE;
		}
		return !$this->errorCode;
	}
	//重定义 id &name
	public function getId() //so that 'id' returns auto-increment id, not login name.
	{
		return $this->_id;
	}
	
	public function getName(){
		return $this->_id;
	}
}