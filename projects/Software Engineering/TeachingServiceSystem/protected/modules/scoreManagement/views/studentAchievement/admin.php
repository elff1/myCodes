<?php
$this->breadcrumbs=array(
	ScoreManagementModule::t('studentScoreManagement','Student Score Management')=>array('courseSelSched/index'),
	ScoreManagementModule::t('studentScoreManagement','Student Achievements analysis'),
);



Yii::app()->clientScript->registerScript('search', "
$('.search-button').click(function(){
	$('.search-form').toggle();
	return false;
});
$('.search-form form').submit(function(){
	$.fn.yiiGridView.update('student-achievement-grid', {
		data: $(this).serialize()
	});
	return false;
});
");
?>



<h1><?php echo ScoreManagementModule::t('studentScoreManagement','welcome to student score management analysis')?></h1>

<?php echo CHtml::link(ScoreManagementModule::t('studentScoreManagement','Advanced Search'),'#',array('class'=>'search-button')); ?>
<div class="search-form" style="display:none">
<?php $this->renderPartial('_search',array(
	'model'=>$model,
)); ?>
</div><!-- search-form -->

<?php $this->widget('zii.widgets.grid.CGridView', array(
	'id'=>'student-achievement-grid',
	'dataProvider'=>$model->search(),
	'filter'=>$model,
	'columns'=>array(
		'id',
		'gpa_major',
		'gpa_total',
		'credit_total',
		'credit_achieve',
		'credit_major_total',
		/*
		'credit_major_achieve',
		*/
	//	array(
	//		'class'=>'CButtonColumn',
	//	),
	),
)); ?>
