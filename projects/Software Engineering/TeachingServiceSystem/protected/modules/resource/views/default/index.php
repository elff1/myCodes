<?php
$this->breadcrumbs=array(
	$this->module->id,
);

$this->menu=array(
    array('label'=>TestOnlineModule::t('core','Resource'), 'url'=>array('/resource/resResource/index', 'uid'=>Yii::app()->user->id)),
    array('label'=>TestOnlineModule::t('core','Assignment'), 'url'=>array('/resource/resAssignment/index')),
    array('label'=>TestOnlineModule::t('core','Homework'), 'url'=>array('/resource/resHomework/index')),
);
?>
<h1><?php echo $this->uniqueId . '/' . $this->action->id; ?></h1>

<p>
This is the view content for action "<?php echo $this->action->id; ?>".
The action belongs to the controller "<?php echo get_class($this); ?>" in the "<?php echo $this->module->id; ?>" module.
</p>

