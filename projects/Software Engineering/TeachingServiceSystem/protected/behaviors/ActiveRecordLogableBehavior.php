<?php
class ActiveRecordLogableBehavior extends CActiveRecordBehavior
{
 
    public function afterSave($event)
    {	
    	$userId = Yii::app()->user->isGuest ? '<Guest>': Yii::app()->user->id;
        if ($this->owner->isNewRecord) {
        	$message = 'User with id '.$userId.' created a record in table '.$this->owner->tableName().' with id '.$this->owner->primaryKey;
			Yii::log($message, 'info', 'db');
        } else {
			$message = 'User with id '.$userId.' updated a record in table '.$this->owner->tableName().' with id '.$this->owner->primaryKey;
			Yii::log($message, 'info', 'db');
        }
    }
 
    public function afterDelete($event)
    {
        $userId = Yii::app()->user->isGuest ? '<Guest>': Yii::app()->user->id;
        $message = 'User with id '.$userId.' deleted a record in table '.$this->owner->tableName().' with id '.$this->owner->primaryKey;
		Yii::log($message, 'info', 'db');
    }
}