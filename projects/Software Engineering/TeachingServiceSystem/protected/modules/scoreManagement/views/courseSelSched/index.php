<?php
$this->breadcrumbs=array(
	//'Personal Infos',
	ScoreManagementModule::t('studentScoreManagement','Student Score Management')
);

$this->menu=array(
	array('label'=>ScoreManagementModule::t('studentScoreManagement','Show Scores and Query'), 'url'=>array('admin')),
	array('label'=>ScoreManagementModule::t('studentScoreManagement','Show Analysis'), 'url'=>array('studentAchievement/admin')),
);
?>

<h1><?php echo ScoreManagementModule::t('studentScoreManagement','welcome to student score management system')?></h1>



<?php //$this->widget('zii.widgets.CListView', array(
	//'dataProvider'=>$dataProvider,
	//'itemView'=>'_view',
//)); 
?>
