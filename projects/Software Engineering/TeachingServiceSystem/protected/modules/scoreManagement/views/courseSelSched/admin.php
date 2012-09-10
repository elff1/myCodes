<?php
$this->breadcrumbs=array(
	ScoreManagementModule::t('studentScoreManagement','Student Score Management')=>array('index'),
	ScoreManagementModule::t('studentScoreManagement','Query'),
);

//$this->menu=array(
//	array('label'=>'List CourseSelSched', 'url'=>array('index')),
//	array('label'=>'Create CourseSelSched', 'url'=>array('create')),
//);

Yii::app()->clientScript->registerScript('searchForStudent', "
$('.search-button').click(function(){
	$('.search-form').toggle();
	return false;
});
$('.search-form form').submit(function(){
	$.fn.yiiGridView.update('course-sel-sched-grid', {
		data: $(this).serialize()
	});
	return false;
});
");
?>

<h1><?php echo ScoreManagementModule::t('studentScoreManagement','welcome to student score management query')?></h1>



<?php echo CHtml::link(ScoreManagementModule::t('studentScoreManagement','Advanced Search'),'#',array('class'=>'search-button')); ?>
<div class="search-form" style="display:none">
<?php $this->renderPartial('_search',array(
	'model'=>$model,
)); ?>
</div><!-- search-form -->

<?php $this->widget('zii.widgets.grid.CGridView', array(
	'id'=>'course-sel-sched-grid',
	'dataProvider'=>$model->searchForStudent(),
	'filter'=>$model,
	'columns'=>array(
		'id',
		//'stu_id',
		'course_id',
		'name',
		'required',
		'repeated',
		'abandoned',
		
		
	
		'year',
		'term',
		'score',
		//array(
		//	'class'=>'CButtonColumn',
		//),
	),
)); ?>
