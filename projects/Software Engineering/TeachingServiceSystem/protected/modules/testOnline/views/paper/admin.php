<?php
$this->breadcrumbs=array(
	'Online Test Subsystem'=>array('/testOnline'),
	'Course List'=>array('default/listCourses'),
	AccountComponent::getSelected_course_name()=>array('paperBank/'),
	AccountComponent::getSelected_paper_id()=>array('paperBank/view', 'id'=>AccountComponent::getSelected_paper_id()),
	'Modify',
);
 
// $this->menu=array(
// 	array('label'=>'List Paper', 'url'=>array('paperBank/view','id'=>AccountComponent::getSelected_paper_id())),
// 	array('label'=>'Create Paper', 'url'=>array('create')),
// );

Yii::app()->clientScript->registerScript('search', "
$('.search-button').click(function(){
	$('.search-form').toggle();
	return false;
});
$('.search-form form').submit(function(){
	$.fn.yiiGridView.update('paper-grid', {
		data: $(this).serialize()
	});
	return false;
});
");
?>

<h1>Manage Questions in Paper</h1>

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

<?php 
$this->widget('zii.widgets.grid.CGridView', array(
	'id'=>'question-bank-grid',
	'dataProvider'=>TestInfoComponent::getQuestionByPaper(AccountComponent::getSelected_paper_id()),
	//'filter'=>QuestionBank::model(),

	'ajaxUpdate'=>false,
	'columns'=>array(
		'id',
		'question',
		'selection_a',
		'selection_b',
		'selection_c',
		'selection_d',
		'type',
		'answer',
		array(
			'class'=>'CButtonColumn','template'=>'{delete}',
				'buttons'=>array(
						'delete' => array(
								'url'=>'Yii::app()->createUrl("testOnline/paper/delete",array("id"=>PaperController::getSelectedPaperProID(AccountComponent::getSelected_paper_id(),$data->id)))',
						),
				)
		),
	),
));

echo "<h2>Select the following questions to be added:</h2>";
?>

<div class="form">
	<?php $form=$this->beginWidget('CActiveForm', array('action'=>array('paper/addQuestions'))); ?>

	<?php
	$this->widget('zii.widgets.grid.CGridView', array(
	    'id'=>'ununsed_question_grid',
	    'dataProvider'=>PaperBankController::getUnusedQuestions(AccountComponent::getSelected_paper_id()),
		//	'ajaxUpdate'=>true,
	    'columns'=>array(
	        'id',
	        'question',
	        'selection_a',
	        'selection_b',
	        'selection_c',
	        'selection_d',
	        'type',
	        'answer',
	        array(
	            'class'=>'CCheckBoxColumn',
	            'selectableRows'=>2,
	            'header'=>'Selected',
	            'id'=>'someChecks',
	        ),
	    ),
	));

	//$this->renderPartial('_dialog'); 
	 ?>

	<div class="row submit">
        <?php echo CHtml::submitButton('Add'); ?>
    </div>
<?php $this->endWidget(); ?>
</div><!-- form -->
