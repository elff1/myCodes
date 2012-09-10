<?php

class InformationManagementModule extends CWebModule
{
	public function init()
	{
		// this method is called when the module is being created
		// you may place code here to customize the module or the application

		// import the module-level models and components
		$this->setImport(array(
			'informationManagement.models.*',
			'informationManagement.components.*',
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
	
	//helper function for translation
	public static function t($category, $message, $params=array(), $source=null, $language=null)
	{
		return Yii::t('InformationManagementModule.'.$category, $message, $params, $source, $language);
	}
}
