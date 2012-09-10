<?php

class TestOnlineModule extends CWebModule
{
	public function init()
	{
		// this method is called when the module is being created
		// you may place code here to customize the module or the application

		// import the module-level models and components
		$this->setImport(array(
			'testOnline.models.*',
			'testOnline.controllers.*',
			'testOnline.components.*',
			'CourseSelection.models.CourseSelSched'
		));
	}

	
	public function beforeControllerAction($controller, $action)
	{
		if(parent::beforeControllerAction($controller, $action))
		{
			// this method is called before any module controller action is performed
			// you may place customized code here
			return true;
		}
		else
			return false;
	}
	
	/**
	 * translate the string into english or chinese
	 * @param string $category
	 * @param string $message
	 * @param string $params
	 * @param string_type $source
	 * @param string $language
	 */
	public static function t($category, $message, $params=array(), $source=null, $language=null)
	{
		return Yii::t('TestOnlineModule.'.$category, $message, $params, $source, $language);
	}
}
