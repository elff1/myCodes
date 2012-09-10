<?php
// the breadcrumbs list
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name(),
		'Papers',
);

// the menu list
if(AccountComponent::getUserType()===UserAuthentication::TYPE_STUDENT|AccountComponent::getUserSelectedType()===UserAuthentication::TYPE_STUDENT){
	$this->menu=array(
			array('label'=>TestOnlineModule::t('core','Historical Performance'), 'url'=>array('statistics/showstu')),
			array('label'=>TestOnlineModule::t('core','Statistics Analysis'), 'url'=>array('statistics/')),
	);
}
else{
	$this->menu=array(
			array('label'=>TestOnlineModule::t('core','QuestionBank'), 'url'=>array('questionBank/')),
			array('label'=>TestOnlineModule::t('core','PaperBank Management'), 'url'=>array('admin')),
	//		array('label'=>TestOnlineModule::t('core','Generate Paper'), 'url'=>array('paperBank/create')),
	//		array('label'=>TestOnlineModule::t('core','Statistics Analysis of Questions'), 'url'=>array('statistics/showprob')),
	//		array('label'=>TestOnlineModule::t('core','Statistics Analysis of Paper'), 'url'=>array('statistics/showpaper')),
			array('label'=>TestOnlineModule::t('core','Statistics Analysis'), 'url'=>array('statistics/')),
	);
}
?>

<!-- the title -->
<h1>Papers of <?php echo AccountComponent::getSelected_course_name();?></h1>

<!-- the main data view -->
<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>