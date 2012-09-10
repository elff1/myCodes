<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Question Banks'=>array('index'),
		'Manage',
);

$this->menu=array(
	array('label'=>TestOnlineModule::t('core','List Questions'), 'url'=>array('index')),
	array('label'=>TestOnlineModule::t('core','Add Question'), 'url'=>array('create')),
//	array('label'=>TestOnlineModule::t('core','Manage Questions'), 'url'=>array('admin')),
	array('label'=>TestOnlineModule::t('core','Batch Add Questions'), 'url'=>array('batchCreate')),
);

Yii::app()->clientScript->registerScript('search', "
$('.search-button').click(function(){
	$('.search-form').toggle();
	return false;
});
$('.search-form form').submit(function(){
	$.fn.yiiGridView.update('question-bank-grid', {
		data: $(this).serialize()
	});
	return false;
});
");
?>

<h1>Manage Question Banks</h1>

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
	'id'=>'question-bank-grid',
	'dataProvider'=>$model->search(),
	'filter'=>$model,
	'columns'=>array(
		'question',
		'selection_a',
		'selection_b',
		'selection_c',
		'selection_d',
		'type',
		'answer',
		array(
			'class'=>'CButtonColumn',
		),
	),
)); ?>
