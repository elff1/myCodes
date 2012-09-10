<?php
$this->breadcrumbs=array(
	'Course Sel Scheds'=>array('index'),
	'Manage',
);

$this->menu=array(
	array('label'=>'List CourseSelSched', 'url'=>array('index')),
	array('label'=>'Create CourseSelSched', 'url'=>array('create')),
);

Yii::app()->clientScript->registerScript('search', "
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

<h1>Manage Course Sel Scheds</h1>

<p>
You may optionally enter a comparison operator (<b>&lt;</b>, <b>&lt;=</b>, <b>&gt;</b>, <b>&gt;=</b>, <b>&lt;&gt;</b>
or <b>=</b>) at the beginning of each of your search values to specify how the comparison should be done.
</p>

<?php echo CHtml::link('Advanced Search','#',array('class'=>'search-button')); ?>
<div class="search-form" style="display:none">
<?php $this->renderPartial('_search',array(
	'model'=>$model,
)); ?>
</div><!-- search-form -->

<?php $this->widget('zii.widgets.grid.CGridView', array(
	'id'=>'course-sel-sched-grid',
	'dataProvider'=>$model->search($id),
	'filter'=>$model,
	'columns'=>array(
		array(
			'class'=>'CLinkColumn',
			'header'=>'CLASS ID',
			'labelExpression'=>'$data["CLASS_ID"]',
			'urlExpression'=>'Yii::app()->createUrl("/site/index",array("CLASS_ID"=>$data->CLASS_ID))', //可以传参数
		),
		
		array(
			'name'=>'course_name',
			'value'=>'$data->cLASS->courseNum->name',
		),
		/*
		array(
			'header'=>Yii::t('base', 'Course Selection'),
			'name'=>'cLASS',
			'value'=>'$data["time"]',
		//	'value'=>'$data->cLASS->courseNum->name',
		),
		*/
		array(
			'header'=>'TIME',
			'name'=>'cLASS',
			'value'=>'$data->timeToStr($data->cLASS->classTimes[0]->time)',
		//	'value'=?'$data["time"]'
		),
	),
)); ?>
