<?php
// the breadcrumbs
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name(),
		AccountComponent::getSelected_paper_id()=>array('paperBank/view', 'id'=>AccountComponent::getSelected_paper_id()),
		'Auto Add',
);
?>

<!-- the auto generation input form -->
<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array('action'=>array('paper/autoAdd'))); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>

	<!-- the number input row -->
	<div class="row">
		<?php echo $form->labelEx($model,'number'); ?>
		<?php echo $form->textField($model,'number'); ?>
	</div>

	<!-- the submit button -->
	<div class="row submit">
        <?php echo CHtml::submitButton('Auto Generate'); ?>
    </div>

<?php $this->endWidget(); ?>

</div>